#include <iostream>
#include <vector>
using namespace std;

struct Stock {
    int stock_ID;
    string stock_Name;
    double stock_Price;
};

int partitionByName(vector<Stock> &arr, int low, int high) {
    string pivot = arr[high].stock_Name;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].stock_Name < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortByName(vector<Stock> &arr, int low, int high) {
    if (low < high) {
        int pi = partitionByName(arr, low, high);
        quickSortByName(arr, low, pi - 1);
        quickSortByName(arr, pi + 1, high);
    }
}

void mergeByPrice(vector<Stock> &arr, int left, int mid, int right) {
    vector<Stock> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (arr[i].stock_Price >= arr[j].stock_Price)
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); k++) {
        arr[left + k] = temp[k];
    }
}

void mergeSortByPrice(vector<Stock> &arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortByPrice(arr, left, mid);
    mergeSortByPrice(arr, mid + 1, right);
    mergeByPrice(arr, left, mid, right);
}

void display(const vector<Stock> &arr) {
    cout << "\nStock_ID\tStock_Name\tStock_Price\n";
    cout << "------------------------------------------\n";
    for (auto &s : arr) {
        cout << s.stock_ID << "\t\t" << s.stock_Name << "\t\t" << s.stock_Price << endl;
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of stocks: ";
    cin >> n;

    vector<Stock> stocks(n);
    for (int i = 0; i < n; i++) {
        cout << "\nEnter details for Stock " << i + 1 << ":\n";
        cout << "Stock ID: ";
        cin >> stocks[i].stock_ID;
        cout << "Stock Name: ";
        cin >> stocks[i].stock_Name;
        cout << "Stock Price: ";
        cin >> stocks[i].stock_Price;
    }

    cout << "\nOriginal Stock List:";
    display(stocks);

    quickSortByName(stocks, 0, n - 1);
    cout << "\nAfter Quick Sort (Alphabetical by Name):";
    display(stocks);

    mergeSortByPrice(stocks, 0, n - 1);
    cout << "\nAfter Merge Sort (Descending by Price):";
    display(stocks);

    return 0;
}
