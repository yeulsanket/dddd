#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct Model {
    int Model_ID;
    char Model_Name[50];
    float Accuracy;
    char Training_Date[20];
    int next;
    bool isEmpty;
    
    Model() {
        Model_ID = -1;
        strcpy(Model_Name, "");
        Accuracy = 0.0;
        strcpy(Training_Date, "");
        next = -1;
        isEmpty = true;
    }
};

class ModelRegistry {
private:
    string filename;
    int tableSize;
    
    int hashFunction(int modelID) {
        return modelID % tableSize;
    }
    
    void initializeFile() {
        fstream file(filename, ios::out | ios::binary);
        Model emptyModel;
        
        for (int i = 0; i < tableSize; i++) {
            file.write((char*)&emptyModel, sizeof(Model));
        }
        file.close();
        cout << "File initialized with " << tableSize << " slots.\n";
    }
    
    Model readRecord(int position) {
        fstream file(filename, ios::in | ios::binary);
        Model model;
        
        file.seekg(position * sizeof(Model), ios::beg);
        file.read((char*)&model, sizeof(Model));
        file.close();
        
        return model;
    }
    
    void writeRecord(int position, Model model) {
        fstream file(filename, ios::in | ios::out | ios::binary);
        
        file.seekp(position * sizeof(Model), ios::beg);
        file.write((char*)&model, sizeof(Model));
        file.close();
    }
    
    int findEmptySlot() {
        for (int i = 0; i < tableSize; i++) {
            Model model = readRecord(i);
            if (model.isEmpty) {
                return i;
            }
        }
        return -1;
    }

public:
    ModelRegistry(string fname, int size) {
        filename = fname;
        tableSize = size;
        
        ifstream checkFile(filename);
        if (!checkFile.good()) {
            checkFile.close();
            initializeFile();
        } else {
            checkFile.close();
        }
    }
    
    void insertModel(int id, string name, float accuracy, string date) {
        Model newModel;
        newModel.Model_ID = id;
        strcpy(newModel.Model_Name, name.c_str());
        newModel.Accuracy = accuracy;
        strcpy(newModel.Training_Date, date.c_str());
        newModel.next = -1;
        newModel.isEmpty = false;
        
        int hashIndex = hashFunction(id);
        Model existing = readRecord(hashIndex);
        
        if (existing.isEmpty) {
            writeRecord(hashIndex, newModel);
            cout << "Model inserted at index " << hashIndex << endl;
        } 
        else {
            cout << "Collision at index " << hashIndex << ". Using chaining...\n";
            
            int currentIndex = hashIndex;
            Model currentModel = existing;
            
            while (currentModel.next != -1) {
                currentIndex = currentModel.next;
                currentModel = readRecord(currentIndex);
            }
            
            int emptySlot = findEmptySlot();
            if (emptySlot == -1) {
                cout << "Error: Hash table is full!\n";
                return;
            }
            
            currentModel.next = emptySlot;
            writeRecord(currentIndex, currentModel);
            
            writeRecord(emptySlot, newModel);
            cout << "Model inserted at index " << emptySlot << " (chained from " << currentIndex << ")\n";
        }
    }
    
    void searchModel(int id) {
        int hashIndex = hashFunction(id);
        Model model = readRecord(hashIndex);
        
        int currentIndex = hashIndex;
        while (currentIndex != -1) {
            model = readRecord(currentIndex);
            
            if (!model.isEmpty && model.Model_ID == id) {
                cout << "\n===== Model Found =====\n";
                cout << "Position: " << currentIndex << endl;
                cout << "Model ID: " << model.Model_ID << endl;
                cout << "Model Name: " << model.Model_Name << endl;
                cout << "Accuracy: " << model.Accuracy << "%" << endl;
                cout << "Training Date: " << model.Training_Date << endl;
                cout << "Next: " << model.next << endl;
                return;
            }
            currentIndex = model.next;
        }
        
        cout << "Model with ID " << id << " not found.\n";
    }
    
    void displayAll() {
        cout << "\n===== All Model Records =====\n";
        for (int i = 0; i < tableSize; i++) {
            Model model = readRecord(i);
            
            if (!model.isEmpty) {
                cout << "\nIndex: " << i << endl;
                cout << "Model ID: " << model.Model_ID << endl;
                cout << "Model Name: " << model.Model_Name << endl;
                cout << "Accuracy: " << model.Accuracy << "%" << endl;
                cout << "Training Date: " << model.Training_Date << endl;
                cout << "Next: " << model.next << endl;
                cout << "------------------------\n";
            }
        }
    }
    
    void deleteModel(int id) {
        int hashIndex = hashFunction(id);
        Model model = readRecord(hashIndex);
        
        int currentIndex = hashIndex;
        int prevIndex = -1;
        
        while (currentIndex != -1) {
            model = readRecord(currentIndex);
            
            if (!model.isEmpty && model.Model_ID == id) {
                if (prevIndex == -1) {
                    if (model.next != -1) {
                        Model nextModel = readRecord(model.next);
                        writeRecord(currentIndex, nextModel);
                    } else {
                        Model emptyModel;
                        writeRecord(currentIndex, emptyModel);
                    }
                } else {
                    Model prevModel = readRecord(prevIndex);
                    prevModel.next = model.next;
                    writeRecord(prevIndex, prevModel);
                    
                    Model emptyModel;
                    writeRecord(currentIndex, emptyModel);
                }
                
                cout << "Model with ID " << id << " deleted successfully.\n";
                return;
            }
            
            prevIndex = currentIndex;
            currentIndex = model.next;
        }
        
        cout << "Model with ID " << id << " not found.\n";
    }
};

int main() {
    ModelRegistry registry("model_registry.dat", 10);
    
    int choice;
    
    do {
        cout << "\n===== AI Model Registry System =====\n";
        cout << "1. Insert Model\n";
        cout << "2. Search Model\n";
        cout << "3. Delete Model\n";
        cout << "4. Display All Models\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int id;
                string name, date;
                float accuracy;
                
                cout << "Enter Model ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Model Name: ";
                getline(cin, name);
                cout << "Enter Accuracy (%): ";
                cin >> accuracy;
                cin.ignore();
                cout << "Enter Training Date (YYYY-MM-DD): ";
                getline(cin, date);
                
                registry.insertModel(id, name, accuracy, date);
                break;
            }
            case 2: {
                int id;
                cout << "Enter Model ID to search: ";
                cin >> id;
                registry.searchModel(id);
                break;
            }
            case 3: {
                int id;
                cout << "Enter Model ID to delete: ";
                cin >> id;
                registry.deleteModel(id);
                break;
            }
            case 4:
                registry.displayAll();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);
    
    return 0;
}