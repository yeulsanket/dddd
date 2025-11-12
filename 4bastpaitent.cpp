#include <iostream>
#include <string>
using namespace std;

class PatientNode {
public:
    int patientID;
    string name;
    int age;
    string medicalHistory;
    PatientNode* left;
    PatientNode* right;
    
    PatientNode() {
        patientID = 0;
        name = "";
        age = 0;
        medicalHistory = "";
        left = NULL;
        right = NULL;
    }
};

class MedicalRecordSystem {
public:
    PatientNode* root;
    
    MedicalRecordSystem() {
        root = NULL;
    }
    
    void registerPatient(int id, string name, int age, string mh) {
        PatientNode* newNode = new PatientNode();
        newNode->patientID = id;
        newNode->name = name;
        newNode->age = age;
        newNode->medicalHistory = mh;
        newNode->left = NULL;
        newNode->right = NULL;
        
        if (root == NULL) {
            root = newNode;
            cout << "Patient " << name << " registered successfully!" << endl;
            return;
        }
        
        PatientNode* current = root;
        PatientNode* parent = NULL;
        
        while (current != NULL) {
            parent = current;
            if (id < current->patientID) {
                current = current->left;
            } else if (id > current->patientID) {
                current = current->right;
            } else {
                cout << "Patient ID already exists!" << endl;
                delete newNode;
                return;
            }
        }
        
        if (id < parent->patientID) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
        
        cout << "Patient " << name << " registered successfully!" << endl;
    }
    
    void accessPatient(int id) {
        PatientNode* current = root;
        
        while (current != NULL) {
            if (id == current->patientID) {
                cout << "\n--- Patient Record ---" << endl;
                cout << "Patient ID: " << current->patientID << endl;
                cout << "Name: " << current->name << endl;
                cout << "Age: " << current->age << endl;
                cout << "Medical History: " << current->medicalHistory << endl;
                cout << "----------------------\n" << endl;
                return;
            } else if (id < current->patientID) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        
        cout << "Patient not found!" << endl;
    }
    
    void updateMedicalHistory(int id, string newHistory) {
        PatientNode* current = root;
        
        while (current != NULL) {
            if (id == current->patientID) {
                current->medicalHistory = newHistory;
                cout << "Medical history updated successfully!" << endl;
                return;
            } else if (id < current->patientID) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        
        cout << "Patient not found!" << endl;
    }
    
    void researchStudyCohort(int minAge, int maxAge) {
        cout << "\n--- Research Study Cohort (Age " << minAge << "-" << maxAge << ") ---" << endl;
        
        if (root == NULL) {
            cout << "No patients in the system." << endl;
            cout << "--------------------------------------------\n" << endl;
            return;
        }
        
        PatientNode* stack[1000];
        int top = -1;
        PatientNode* current = root;
        int count = 0;
        
        while (current != NULL || top != -1) {
            while (current != NULL) {
                top++;
                stack[top] = current;
                current = current->left;
            }
            
            current = stack[top];
            top--;
            
            if (current->age >= minAge && current->age <= maxAge) {
                cout << "ID: " << current->patientID << " | Name: " << current->name 
                     << " | Age: " << current->age << " | History: " << current->medicalHistory << endl;
                count++;
            }
            
            current = current->right;
        }
        
        if (count == 0) {
            cout << "No patients found in this age range." << endl;
        } else {
            cout << "Total patients found: " << count << endl;
        }
        cout << "--------------------------------------------\n" << endl;
    }
    
    void dischargePatient(int id) {
        if (root == NULL) {
            cout << "Patient not found!" << endl;
            return;
        }
        
        PatientNode* current = root;
        PatientNode* parent = NULL;
        
        while (current != NULL && current->patientID != id) {
            parent = current;
            if (id < current->patientID) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        
        if (current == NULL) {
            cout << "Patient not found!" << endl;
            return;
        }
        
        if (current->left == NULL && current->right == NULL) {
            if (parent == NULL) {
                root = NULL;
            } else if (parent->left == current) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
            delete current;
            cout << "Patient ID " << id << " has been discharged successfully!" << endl;
        }
        else if (current->left == NULL) {
            if (parent == NULL) {
                root = current->right;
            } else if (parent->left == current) {
                parent->left = current->right;
            } else {
                parent->right = current->right;
            }
            delete current;
            cout << "Patient ID " << id << " has been discharged successfully!" << endl;
        }
        else if (current->right == NULL) {
            if (parent == NULL) {
                root = current->left;
            } else if (parent->left == current) {
                parent->left = current->left;
            } else {
                parent->right = current->left;
            }
            delete current;
            cout << "Patient ID " << id << " has been discharged successfully!" << endl;
        }
        else {
            PatientNode* successorParent = current;
            PatientNode* successor = current->right;
            
            while (successor->left != NULL) {
                successorParent = successor;
                successor = successor->left;
            }
            
            current->patientID = successor->patientID;
            current->name = successor->name;
            current->age = successor->age;
            current->medicalHistory = successor->medicalHistory;
            
            if (successorParent->left == successor) {
                successorParent->left = successor->right;
            } else {
                successorParent->right = successor->right;
            }
            
            delete successor;
            cout << "Patient ID " << id << " has been discharged successfully!" << endl;
        }
    }
};

int main() {
    MedicalRecordSystem hospital;
    int choice, id, age, minAge, maxAge;
    string name, history;
    
    while (true) {
        cout << "\n=== Medical Patient Record System ===" << endl;
        cout << "1. Register New Patient" << endl;
        cout << "2. Access Patient Record" << endl;
        cout << "3. Update Medical History" << endl;
        cout << "4. Research Study Cohort (Age Range)" << endl;
        cout << "5. Discharge Patient" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (choice == 1) {
            cout << "Enter Patient ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Medical History: ";
            cin.ignore();
            getline(cin, history);
            hospital.registerPatient(id, name, age, history);
        } 
        else if (choice == 2) {
            cout << "Enter Patient ID: ";
            cin >> id;
            hospital.accessPatient(id);
        } 
        else if (choice == 3) {
            cout << "Enter Patient ID: ";
            cin >> id;
            cout << "Enter New Medical History: ";
            cin.ignore();
            getline(cin, history);
            hospital.updateMedicalHistory(id, history);
        } 
        else if (choice == 4) {
            cout << "Enter Minimum Age: ";
            cin >> minAge;
            cout << "Enter Maximum Age: ";
            cin >> maxAge;
            hospital.researchStudyCohort(minAge, maxAge);
        }
        else if (choice == 5) {
            cout << "Enter Patient ID to discharge: ";
            cin >> id;
            hospital.dischargePatient(id);
        }
        else if (choice == 6) {
            cout << "Exiting system..." << endl;
            break;
        } 
        else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}
