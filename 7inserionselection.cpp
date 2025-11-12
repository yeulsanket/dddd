#include <iostream>
#include <string>
using namespace std;

class Movie {
public:
    int movieID;
    string movieName;
    int moviePopularity;
    string movieReleaseDate;
    
    Movie() {
        movieID = 0;
        movieName = "";
        moviePopularity = 0;
        movieReleaseDate = "";
    }
    
    Movie(int id, string name, int pop, string date) {
        movieID = id;
        movieName = name;
        moviePopularity = pop;
        movieReleaseDate = date;
    }
};

class MovieBookingSystem {
private:
    Movie movies[100];
    int count;
    
public:
    MovieBookingSystem() {
        count = 0;
    }
    
    void addMovie(int id, string name, int pop, string date) {
        if(count >= 100) {
            cout << "Cannot add more movies!" << endl;
            return;
        }
        
        // Check if movie ID already exists
        for(int i = 0; i < count; i++) {
            if(movies[i].movieID == id) {
                cout << "Movie ID already exists!" << endl;
                return;
            }
        }
        
        movies[count] = Movie(id, name, pop, date);
        count++;
        cout << "Movie added successfully!" << endl;
    }
    
    void insertionSortByPopularity() {
        if(count == 0) {
            cout << "No movies to sort!" << endl;
            return;
        }
        
        for(int i = 1; i < count; i++) {
            Movie key = movies[i];
            int j = i - 1;
            
            // Sort by popularity in descending order (highest first)
            while(j >= 0 && movies[j].moviePopularity < key.moviePopularity) {
                movies[j + 1] = movies[j];
                j = j - 1;
            }
            movies[j + 1] = key;
        }
        
        cout << "Movies sorted by Popularity (Highest to Lowest) using Insertion Sort!" << endl;
        displayMovies();
    }
    
    void selectionSortByReleaseDate() {
        if(count == 0) {
            cout << "No movies to sort!" << endl;
            return;
        }
        
        for(int i = 0; i < count - 1; i++) {
            int minIndex = i;
            
            for(int j = i + 1; j < count; j++) {
                // Sort by release date in ascending order (oldest first)
                if(movies[j].movieReleaseDate < movies[minIndex].movieReleaseDate) {
                    minIndex = j;
                }
            }
            
            if(minIndex != i) {
                Movie temp = movies[i];
                movies[i] = movies[minIndex];
                movies[minIndex] = temp;
            }
        }
        
        cout << "Movies sorted by Release Date (Oldest to Newest) using Selection Sort!" << endl;
        displayMovies();
    }
    
    void searchMovieByName(string name) {
        if(count == 0) {
            cout << "No movies available!" << endl;
            return;
        }
        
        bool found = false;
        cout << "\nSearch Results for: " << name << endl;
        cout << "------------------------------------------------------------" << endl;
        
        for(int i = 0; i < count; i++) {
            if(movies[i].movieName.find(name) != string::npos) {
                cout << "ID: " << movies[i].movieID << endl;
                cout << "Name: " << movies[i].movieName << endl;
                cout << "Popularity: " << movies[i].moviePopularity << endl;
                cout << "Release Date: " << movies[i].movieReleaseDate << endl;
                cout << "------------------------------------------------------------" << endl;
                found = true;
            }
        }
        
        if(!found) {
            cout << "No movies found with that name!" << endl;
        }
    }
    
    void displayMovies() {
        if(count == 0) {
            cout << "No movies available!" << endl;
            return;
        }
        
        cout << "\nAll Movies (" << count << " movies):" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "ID\tName\t\t\tPopularity\tRelease Date" << endl;
        cout << "------------------------------------------------------------" << endl;
        
        for(int i = 0; i < count; i++) {
            // Adjust formatting for better display
            string displayName = movies[i].movieName;
            if(displayName.length() > 15) {
                displayName = displayName.substr(0, 12) + "...";
            }
            
            cout << movies[i].movieID << "\t" 
                 << displayName << "\t\t" 
                 << movies[i].moviePopularity << "\t\t"
                 << movies[i].movieReleaseDate << endl;
        }
        cout << endl;
    }
    
    void displayStatistics() {
        if(count == 0) {
            cout << "No movies available for statistics!" << endl;
            return;
        }
        
        int totalPopularity = 0;
        int maxPopularity = movies[0].moviePopularity;
        int minPopularity = movies[0].moviePopularity;
        string mostPopularMovie = movies[0].movieName;
        string leastPopularMovie = movies[0].movieName;
        
        for(int i = 0; i < count; i++) {
            totalPopularity += movies[i].moviePopularity;
            
            if(movies[i].moviePopularity > maxPopularity) {
                maxPopularity = movies[i].moviePopularity;
                mostPopularMovie = movies[i].movieName;
            }
            
            if(movies[i].moviePopularity < minPopularity) {
                minPopularity = movies[i].moviePopularity;
                leastPopularMovie = movies[i].movieName;
            }
        }
        
        double averagePopularity = (double)totalPopularity / count;
        
        cout << "\nMovie Statistics:" << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "Total Movies: " << count << endl;
        cout << "Average Popularity: " << averagePopularity << endl;
        cout << "Most Popular Movie: " << mostPopularMovie << " (" << maxPopularity << ")" << endl;
        cout << "Least Popular Movie: " << leastPopularMovie << " (" << minPopularity << ")" << endl;
        cout << "------------------------------------------------------------" << endl;
    }
};

int main() {
    MovieBookingSystem system;
    int choice, id, popularity;
    string name, date;
    
    cout << "============================================" << endl;
    cout << "     MOVIE TICKET BOOKING SYSTEM" << endl;
    cout << "  Sorting using Insertion and Selection Sort" << endl;
    cout << "============================================" << endl;
    
    // Add some sample movies
    system.addMovie(1, "Avengers: Endgame", 95, "2023-05-01");
    system.addMovie(2, "Avatar: The Way of Water", 88, "2023-12-15");
    system.addMovie(3, "Titanic", 92, "2023-01-20");
    system.addMovie(4, "The Dark Knight", 98, "2023-03-10");
    system.addMovie(5, "Inception", 90, "2023-07-05");
    
    while(true) {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "1. Add New Movie" << endl;
        cout << "2. Display All Movies" << endl;
        cout << "3. Sort by Popularity (Insertion Sort)" << endl;
        cout << "4. Sort by Release Date (Selection Sort)" << endl;
        cout << "5. Search Movie by Name" << endl;
        cout << "6. Display Statistics" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice (1-7): ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
                cout << "\n--- Add New Movie ---" << endl;
                cout << "Enter Movie ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Movie Name: ";
                getline(cin, name);
                cout << "Enter Popularity (1-100): ";
                cin >> popularity;
                cin.ignore();
                cout << "Enter Release Date (YYYY-MM-DD): ";
                getline(cin, date);
                system.addMovie(id, name, popularity, date);
                break;
                
            case 2:
                system.displayMovies();
                break;
                
            case 3:
                system.insertionSortByPopularity();
                break;
                
            case 4:
                system.selectionSortByReleaseDate();
                break;
                
            case 5:
                cout << "\n--- Search Movie ---" << endl;
                cout << "Enter movie name to search: ";
                getline(cin, name);
                system.searchMovieByName(name);
                break;
                
            case 6:
                system.displayStatistics();
                break;
                
            case 7:
                cout << "\nThank you for using Movie Ticket Booking System!" << endl;
                cout << "Goodbye!" << endl;
                return 0;
                
            default:
                cout << "Invalid choice! Please enter 1-7." << endl;
        }
    }
    
    return 0;
}

