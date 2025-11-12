#include <iostream>
#include <string>
using namespace std;

class Ticket {
    int ticketNo;
    string customerName;
    string issue;

public:
    Ticket() {
        ticketNo = -1;
        customerName = "";
        issue = "";
    }

    Ticket(int tno, string cname, string iss) {
        ticketNo = tno;
        customerName = cname;
        issue = iss;
    }

    void display() {
        cout << "Ticket No: " << ticketNo
             << " | Customer: " << customerName
             << " | Issue: " << issue << "\n";
    }

    int getTicketNo() { return ticketNo; }
    string getName() { return customerName; }
    string getIssue() { return issue; }
};

class CircularQueue {
    int size;
    Ticket *arr;
    int front, rear;
    int count;

public:
    CircularQueue(int n) {
        arr = new Ticket[n];
        size = n;
        front = -1;
        rear = -1;
        count = 0;
    }

    bool isEmpty() {
        return (front == -1);
    }

    bool isFull() {
        return ((rear + 1) % size == front);
    }

    void submitTicket(int tno, string cname, string issue) {
        if (isFull()) {
            cout << "Queue Overflow! Cannot accept more tickets.\n";
            return;
        }
        if (front == -1) { 
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % size;
        }
        arr[rear] = Ticket(tno, cname, issue);
        count++;
        cout << "Ticket Submitted Successfully! Ticket No: " << tno << "\n";
    }

    void resolveTicket() {
        if (isEmpty()) {
            cout << "No tickets to resolve.\n";
            return;
        }
        cout << "Resolving -> ";
        arr[front].display();

        if (front == rear) { 
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % size;
        }
        count--;
    }

    void checkNextTicket() {
        if (isEmpty()) {
            cout << "No tickets in the queue.\n";
            return;
        }
        cout << "Next Ticket -> ";
        arr[front].display();
    }

    void displayStatus() {
        if (isEmpty()) {
            cout << "Queue is Empty. No tickets pending.\n";
            return;
        }
        cout << "Total Tickets in Queue: " << count << "\n";
        int i = front;
        while (true) {
            arr[i].display();
            if (i == rear) break;
            i = (i + 1) % size;
        }
    }
};

int main() {
    CircularQueue q(5);
    int choice, tno = 1;
    string name, issue;

    do {
        cout << "\n--- Customer Support System ---\n";
        cout << "1. Submit Ticket\n";
        cout << "2. Resolve Ticket\n";
        cout << "3. Check Next Ticket\n";
        cout << "4. Display Queue Status\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Customer Name: ";
            cin >> name;
            cin.ignore();
            cout << "Enter Issue: ";
            getline(cin, issue);
            q.submitTicket(tno++, name, issue);
            break;
        case 2:
            q.resolveTicket();
            break;
        case 3:
            q.checkNextTicket();
            break;
        case 4:
            q.displayStatus();
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid Choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
