#include <iostream>
#include <string>
using namespace std;

class Image {
public:
    int imageID;
    string filename;
    string resolution;
    string tag;
    Image* next;
    
    Image(int id, string fname, string res, string t) {
        imageID = id;
        filename = fname;
        resolution = res;
        tag = t;
        next = nullptr;
    }
};

class ImageGallery {
private:
    Image* head;
    Image* current;
    
public:
    ImageGallery() {
        head = nullptr;
        current = nullptr;
    }
    
    ~ImageGallery() {
        Image* temp = head;
        while (temp) {
            Image* del = temp;
            temp = temp->next;
            delete del;
        }
    }
    
    void addImage(int id, string fname, string res, string tag) {
        Image* newImg = new Image(id, fname, res, tag);
        if (!head) {
            head = newImg;
            current = head;
            cout << "Image added as first entry" << endl;
            return;
        }
        Image* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newImg;
        cout << "Image added successfully" << endl;
    }
    
    void deleteImage(int id) {
        if (!head) {
            cout << "No images to delete" << endl;
            return;
        }
        if (head->imageID == id) {
            Image* del = head;
            head = head->next;
            if (current == del) current = head;
            delete del;
            cout << "Image deleted successfully" << endl;
            return;
        }
        Image* temp = head;
        while (temp->next && temp->next->imageID != id) {
            temp = temp->next;
        }
        if (temp->next) {
            Image* del = temp->next;
            temp->next = del->next;
            if (current == del) current = head;
            delete del;
            cout << "Image deleted successfully" << endl;
        } else {
            cout << "Image not found" << endl;
        }
    }
    
    void showCurrent() {
        if (!current) {
            cout << "No images available" << endl;
            return;
        }
        cout << "Current Image:" << endl;
        cout << "ID: " << current->imageID 
             << " | File: " << current->filename
             << " | Resolution: " << current->resolution
             << " | Tag: " << current->tag << endl;
    }
    
    void nextImage() {
        if (!current) {
            cout << "No images available" << endl;
            return;
        }
        if (current->next) {
            current = current->next;
            showCurrent();
        } else {
            cout << "End of gallery reached" << endl;
        }
    }
    
    void resetToStart() {
        current = head;
        cout << "Reset to start of gallery" << endl;
    }
    
    void displayAll() {
        if (!head) {
            cout << "Gallery is empty" << endl;
            return;
        }
        cout << "All Images:" << endl;
        Image* temp = head;
        while (temp) {
            cout << "ID: " << temp->imageID
                 << " | File: " << temp->filename
                 << " | Resolution: " << temp->resolution
                 << " | Tag: " << temp->tag << endl;
            temp = temp->next;
        }
    }
};

int main() {
    ImageGallery gallery;
    int choice, id;
    string filename, resolution, tag;
    
    cout << "Image Gallery System" << endl;
    
    while(true) {
        cout << "\nMenu" << endl;
        cout << "1. Add Image" << endl;
        cout << "2. Delete Image" << endl;
        cout << "3. Show Current Image" << endl;
        cout << "4. Next Image" << endl;
        cout << "5. Reset to Start" << endl;
        cout << "6. Display All Images" << endl;
        cout << "7. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
                cout << "Enter Image ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Filename: ";
                getline(cin, filename);
                cout << "Enter Resolution: ";
                getline(cin, resolution);
                cout << "Enter Tag: ";
                getline(cin, tag);
                gallery.addImage(id, filename, resolution, tag);
                break;
                
            case 2:
                cout << "Enter Image ID to delete: ";
                cin >> id;
                gallery.deleteImage(id);
                break;
                
            case 3:
                gallery.showCurrent();
                break;
                
            case 4:
                gallery.nextImage();
                break;
                
            case 5:
                gallery.resetToStart();
                break;
                
            case 6:
                gallery.displayAll();
                break;
                
            case 7:
                cout << "Goodbye!" << endl;
                return 0;
                
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}
