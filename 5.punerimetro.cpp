





#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <climits>
using namespace std;

struct MetroStation {
    int Station_ID;
    string Station_Name;
    string Metro_Line;
    bool is_Transfer_Station;
    int daily_ridership;
    double daily_revenue;
    
    MetroStation() {
        Station_ID = 0;
        Station_Name = "";
        Metro_Line = "";
        is_Transfer_Station = false;
        daily_ridership = 0;
        daily_revenue = 0.0;
    }
    
    MetroStation(int id, string name, string line, bool transfer, int ridership, double revenue) {
        Station_ID = id;
        Station_Name = name;
        Metro_Line = line;
        is_Transfer_Station = transfer;
        daily_ridership = ridership;
        daily_revenue = revenue;
    }
};

class MetroNetwork {
private:
    map<int, MetroStation> stations;
    map<int, vector<int>> adjacencyList;
    
    void DFSUtil(int stationID, map<int, bool>& visited) {
        visited[stationID] = true;
        cout << stations[stationID].Station_Name << " (ID: " << stationID << ") -> ";
        
        for (int neighbor : adjacencyList[stationID]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }
    
public:
    void addStation(int id, string name, string line, bool transfer, int ridership, double revenue) {
        MetroStation station(id, name, line, transfer, ridership, revenue);
        stations[id] = station;
        adjacencyList[id] = vector<int>();
        cout << "Station added: " << name << endl;
    }
    
    void addConnection(int station1, int station2) {
        adjacencyList[station1].push_back(station2);
        adjacencyList[station2].push_back(station1);
        cout << "Connection added between Station " << station1 << " and Station " << station2 << endl;
    }
    
    void displayAllStations() {
        cout << "\n===== All Metro Stations =====\n";
        for (auto& pair : stations) {
            MetroStation s = pair.second;
            cout << "\nStation ID: " << s.Station_ID << endl;
            cout << "Station Name: " << s.Station_Name << endl;
            cout << "Metro Line: " << s.Metro_Line << endl;
            cout << "Transfer Station: " << (s.is_Transfer_Station ? "Yes" : "No") << endl;
            cout << "Daily Ridership: " << s.daily_ridership << endl;
            cout << "Daily Revenue: Rs. " << s.daily_revenue << endl;
            cout << "Connected to: ";
            for (int neighbor : adjacencyList[s.Station_ID]) {
                cout << stations[neighbor].Station_Name << " ";
            }
            cout << endl;
            cout << "------------------------\n";
        }
    }
    
    void findMaxRevenueStation() {
        if (stations.empty()) {
            cout << "No stations in the network!\n";
            return;
        }
        
        double maxRevenue = -1;
        int maxStationID = -1;
        
        for (auto& pair : stations) {
            if (pair.second.daily_revenue > maxRevenue) {
                maxRevenue = pair.second.daily_revenue;
                maxStationID = pair.first;
            }
        }
        
        cout << "\n===== Station with Maximum Revenue =====\n";
        MetroStation s = stations[maxStationID];
        cout << "Station Name: " << s.Station_Name << endl;
        cout << "Station ID: " << s.Station_ID << endl;
        cout << "Daily Revenue: Rs. " << s.daily_revenue << endl;
    }
    
    void findMaxMinRidershipStations() {
        if (stations.empty()) {
            cout << "No stations in the network!\n";
            return;
        }
        
        int maxRidership = INT_MIN;
        int minRidership = INT_MAX;
        int maxStationID = -1;
        int minStationID = -1;
        
        for (auto& pair : stations) {
            if (pair.second.daily_ridership > maxRidership) {
                maxRidership = pair.second.daily_ridership;
                maxStationID = pair.first;
            }
            if (pair.second.daily_ridership < minRidership) {
                minRidership = pair.second.daily_ridership;
                minStationID = pair.first;
            }
        }
        
        cout << "\n===== Maximum Ridership Station =====\n";
        MetroStation maxS = stations[maxStationID];
        cout << "Station Name: " << maxS.Station_Name << endl;
        cout << "Station ID: " << maxS.Station_ID << endl;
        cout << "Daily Ridership: " << maxS.daily_ridership << endl;
        
        cout << "\n===== Minimum Ridership Station =====\n";
        MetroStation minS = stations[minStationID];
        cout << "Station Name: " << minS.Station_Name << endl;
        cout << "Station ID: " << minS.Station_ID << endl;
        cout << "Daily Ridership: " << minS.daily_ridership << endl;
    }
    
    void findElevatedStations() {
        cout << "\n===== Elevated Metro Stations =====\n";
        bool found = false;
        for (auto& pair : stations) {
            if (pair.second.Metro_Line == "Elevated") {
                cout << "- " << pair.second.Station_Name << " (ID: " << pair.first << ")\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No elevated stations found.\n";
        }
    }
    
    void findUndergroundStations() {
        cout << "\n===== Underground Metro Stations =====\n";
        bool found = false;
        for (auto& pair : stations) {
            if (pair.second.Metro_Line == "Underground") {
                cout << "- " << pair.second.Station_Name << " (ID: " << pair.first << ")\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No underground stations found.\n";
        }
    }
    
    void DFS(int startStationID) {
        if (stations.find(startStationID) == stations.end()) {
            cout << "Station ID " << startStationID << " not found!\n";
            return;
        }
        
        cout << "\n===== DFS Traversal from Station " << startStationID << " =====\n";
        map<int, bool> visited;
        for (auto& pair : stations) {
            visited[pair.first] = false;
        }
        
        DFSUtil(startStationID, visited);
        cout << "END\n";
    }
    
    void BFS(int startStationID) {
        if (stations.find(startStationID) == stations.end()) {
            cout << "Station ID " << startStationID << " not found!\n";
            return;
        }
        
        cout << "\n===== BFS Traversal from Station " << startStationID << " =====\n";
        map<int, bool> visited;
        for (auto& pair : stations) {
            visited[pair.first] = false;
        }
        
        queue<int> q;
        q.push(startStationID);
        visited[startStationID] = true;
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << stations[current].Station_Name << " (ID: " << current << ") -> ";
            
            for (int neighbor : adjacencyList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << "END\n";
    }
};

int main() {
    MetroNetwork metro;
    int choice;
    
    do {
        cout << "\n===== PUNERI METRO ROUTE PLANNER =====\n";
        cout << "1. Add Station\n";
        cout << "2. Add Connection between Stations\n";
        cout << "3. Display All Stations\n";
        cout << "4. Find Station with Maximum Revenue\n";
        cout << "5. Find Stations with Max & Min Ridership\n";
        cout << "6. Find Elevated Route Stations\n";
        cout << "7. Find Underground Route Stations\n";
        cout << "8. DFS Traversal\n";
        cout << "9. BFS Traversal\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int id, ridership;
                string name, line;
                bool transfer;
                double revenue;
                
                cout << "Enter Station ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Station Name: ";
                getline(cin, name);
                cout << "Enter Metro Line (Elevated/Underground): ";
                getline(cin, line);
                cout << "Is Transfer Station? (1 for Civil Court, 0 for others): ";
                cin >> transfer;
                cout << "Enter Daily Ridership: ";
                cin >> ridership;
                cout << "Enter Daily Revenue (Rs.): ";
                cin >> revenue;
                
                metro.addStation(id, name, line, transfer, ridership, revenue);
                break;
            }
            case 2: {
                int station1, station2;
                cout << "Enter first Station ID: ";
                cin >> station1;
                cout << "Enter second Station ID: ";
                cin >> station2;
                metro.addConnection(station1, station2);
                break;
            }
            case 3:
                metro.displayAllStations();
                break;
            case 4:
                metro.findMaxRevenueStation();
                break;
            case 5:
                metro.findMaxMinRidershipStations();
                break;
            case 6:
                metro.findElevatedStations();
                break;
            case 7:
                metro.findUndergroundStations();
                break;
            case 8: {
                int startID;
                cout << "Enter starting Station ID for DFS: ";
                cin >> startID;
                metro.DFS(startID);
                break;
            }
            case 9: {
                int startID;
                cout << "Enter starting Station ID for BFS: ";
                cin >> startID;
                metro.BFS(startID);
                break;
            }
            case 10:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 10);
    
    return 0;
}
