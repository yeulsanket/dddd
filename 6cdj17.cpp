#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <climits>
using namespace std;


struct Edge {
    string destination;
    int weight; // weight can represent cost, duration, or fuel
};

// Graph class
class AirlineNetwork {
private:
    map<string, vector<Edge>> adjList; // adjacency list representation

public:
    // Add connection between two airports (undirected)
    void addFlight(string src, string dest, int cost) {
        adjList[src].push_back({dest, cost});
        adjList[dest].push_back({src, cost});
    }

    // Display flight network
    void displayNetwork() {
        cout << "\n✈️ Airline Route Network:\n";
        for (auto &p : adjList) {
            cout << p.first << " --> ";
            for (auto &e : p.second) {
                cout << "(" << e.destination << ", " << e.weight << ") ";
            }
            cout << endl;
        }
    }

    // Dijkstra’s Algorithm
    void dijkstra(string source) {
        map<string, int> distance;  // shortest distance from source
        map<string, string> parent; // to reconstruct path

        // Initialize all distances as infinity
        for (auto &node : adjList)
            distance[node.first] = INT_MAX;

        // Min-heap priority queue (distance, airport)
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

        // Start from source
        distance[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            string current = pq.top().second;
            int dist = pq.top().first;
            pq.pop();

            // Explore neighbors
            for (auto &edge : adjList[current]) {
                int newDist = dist + edge.weight;

                if (newDist < distance[edge.destination]) {
                    distance[edge.destination] = newDist;
                    parent[edge.destination] = current;
                    pq.push({newDist, edge.destination});
                }
            }
        }

        // Display shortest paths
        cout << "\n🧭 Shortest Route from " << source << ":\n";
        for (auto &d : distance) {
            cout << "To " << d.first << " → Cost: " << d.second;
            if (d.first != source) {
                cout << " | Path: ";
                printPath(parent, source, d.first);
            }
            cout << endl;
        }
    }

    // Helper function to print path recursively
    void printPath(map<string, string> &parent, string src, string dest) {
        if (dest == src) {
            cout << src;
            return;
        }
        if (parent.find(dest) == parent.end()) {
            cout << "No path";
            return;
        }
        printPath(parent, src, parent[dest]);
        cout << " -> " << dest;
    }
};

int main() {
    AirlineNetwork airline;
    int choice, cost;
    string src, dest, source;

    do {
        cout << "\n===== ✈️ AIRLINE ROUTE OPTIMIZATION MENU =====\n";
        cout << "1. Add Flight Route (Edge)\n";
        cout << "2. Display Airline Network\n";
        cout << "3. Find Cheapest/Fastest Route using Dijkstra\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Source Airport: ";
            cin >> src;
            cout << "Enter Destination Airport: ";
            cin >> dest;
            cout << "Enter Cost/Time/Fuel Weight: ";
            cin >> cost;
            airline.addFlight(src, dest, cost);
            break;

        case 2:
            airline.displayNetwork();
            break;

        case 3:
            cout << "Enter Source Airport: ";
            cin >> source;
            airline.dijkstra(source);
            break;

        case 4:
            cout << "👋 Exiting Airline Route System...\n";
            break;

        default:
            cout << "❌ Invalid choice! Try again.\n";
        }

    } while (choice != 4);

    return 0;
}