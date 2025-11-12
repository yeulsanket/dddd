#include<iostream>
#include<string>
using namespace std;

struct Hashtag {
    string name;
    int frequency;
};

void heapify(Hashtag arr[], int index, int n) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < n && arr[left].frequency > arr[largest].frequency) {
        largest = left;
    }
    if (right < n && arr[right].frequency > arr[largest].frequency) {
        largest = right;
    }
    if (largest != index) {
        swap(arr[largest], arr[index]);
        heapify(arr, largest, n);
    }
}

void buildMaxHeap(Hashtag arr[], int n) {
    for (int i = (n - 1) / 2; i >= 0; i--) {
        heapify(arr, i, n);
    }
}

void heapSort(Hashtag arr[], int n) {
    buildMaxHeap(arr, n);
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, 0, i);
    }
}

void displayTopK(Hashtag arr[], int n, int k) {
    cout << "\n========================================" << endl;
    cout << "   TOP " << k << " TRENDING HASHTAGS" << endl;
    cout << "========================================" << endl;
    
    for (int i = n - 1; i >= n - k && i >= 0; i--) {
        cout << (n - i) << ". #" << arr[i].name 
             << " - " << arr[i].frequency << " uses" << endl;
    }
    cout << "========================================" << endl;
}

int main() {
    int n;
    cout << "Enter the number of hashtags: ";
    cin >> n;
    
    Hashtag* hashtags = new Hashtag[n];
    
    cout << "\nEnter hashtag name and frequency (usage count):\n";
    for (int i = 0; i < n; i++) {
        cout << "Hashtag " << (i + 1) << " name: ";
        cin >> hashtags[i].name;
        cout << "Frequency: ";
        cin >> hashtags[i].frequency;
    }
    
    int k = 5;
    
    heapSort(hashtags, n);
    
    displayTopK(hashtags, n, k);
    
    delete[] hashtags;
    return 0;
}