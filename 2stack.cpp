#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string data;
    Node* next;
    
    Node(string val) {
        data = val;
        next = NULL;
    }
};

class Stack {
    Node* top;
    
public:
    Stack() { 
        top = NULL; 
    }
    
    void push(string val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }
    
    string pop() {
        if (top == NULL) return "";
        string val = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return val;
    }
    
    bool isEmpty() {
        return top == NULL;
    }
    
    void clear() {
        while (!isEmpty()) pop();
    }
    
    // NEW: Display function for Stack
    void display(string stackName) {
        if (isEmpty()) {
            cout << stackName << ": Empty" << endl;
            return;
        }
        
        cout << stackName << ": ";
        Node* temp = top;
        while (temp != NULL) {
            cout << temp->data;
            if (temp->next != NULL) cout << " ← ";
            temp = temp->next;
        }
        cout << " (Top)" << endl;
    }
};

class TextEditor {
    Stack undoStack, redoStack;
    
public:
    void perform(string op) {
        cout << "Done: " << op << endl;
        undoStack.push(op);
        redoStack.clear();
    }
    
    void undo() {
        if (undoStack.isEmpty()) {
            cout << "Nothing to undo!" << endl;
            return;
        }
        string op = undoStack.pop();
        cout << "Undo: " << op << endl;
        redoStack.push(op);
    }
    
    void redo() {
        if (redoStack.isEmpty()) {
            cout << "Nothing to redo!" << endl;
            return;
        }
        string op = redoStack.pop();
        cout << "Redo: " << op << endl;
        undoStack.push(op);
    }
    
    void displayStacks() {
        cout << "\n=== Current Stack Status ===" << endl;
        undoStack.display("Undo Stack");
        redoStack.display("Redo Stack");
        cout << "===========================" << endl;
    }
};

int main() {
    TextEditor editor;
    int choice;
    string op;
    
    do {
        cout << "\n1. Perform Operation" << endl;
        cout << "2. Undo" << endl;
        cout << "3. Redo" << endl;
        cout << "4. Display Stacks" << endl;  // NEW OPTION
        cout << "5. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                cout << "Enter operation: ";
                getline(cin, op);
                editor.perform(op);
                break;
                
            case 2:
                editor.undo();
                break;
                
            case 3:
                editor.redo();
                break;
                
            case 4:  
                editor.displayStacks();
                break;
                
            case 5:
                cout << "Exiting..." << endl;
                break;
                
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);
    
    return 0;
}

