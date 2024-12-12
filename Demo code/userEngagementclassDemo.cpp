#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <tuple>

using namespace std;

const double learningRate = 0.1; 
const int numRounds = 10;        

// Function to initialize equal weights for all genres
vector<double> initializeWeights(int numGenres) {
    return vector<double>(numGenres, 1.0);
}

// Function to select a genre based on current weight distribution
int selectGenre(const vector<double>& weights) {
    double totalWeight = accumulate(weights.begin(), weights.end(), 0.0);
    double randomValue = (double)rand() / RAND_MAX * totalWeight;
    double cumulativeWeight = 0.0;

    for (int i = 0; i < weights.size(); ++i) {
        cumulativeWeight += weights[i];
        if (randomValue <= cumulativeWeight) {
            return i;
        }
    }
    return weights.size() - 1;
}

// Function to load titles and genres from CSV
void loadDataset(const string& filename, map<string, vector<string>>& titles, vector<string>& genres) {
    ifstream file(filename);
    string line, title, genre;
    getline(file, line); // Skip the header line

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, title, ',');
        getline(ss, genre, ',');

        titles[genre].push_back(title);
        if (find(genres.begin(), genres.end(), genre) == genres.end()) {
            genres.push_back(genre);
        }
    }
}

// Function to save data for plotting
void saveRoundData(const string& filename, const vector<string>& genres, const vector<double>& weights, int round) {
    ofstream file;
    if (round == 1) {
        file.open(filename);
        file << "Round";
        for (const string& genre : genres) {
            file << "," << genre;
        }
        file << endl;
    } else {
        file.open(filename, ios::app);
    }

    file << round;
    for (double weight : weights) {
        file << "," << weight;
    }
    file << endl;

    file.close();
}

// Function to display video recommendations in a tabular format
void displayRecommendations(const vector<string>& selectedTitles, const vector<string>& selectedGenres) {
    cout << left << setw(5) << "No." << setw(50) << "Title" << "Genre" << endl;
    cout << string(65, '-') << endl;

    for (int i = 0; i < selectedTitles.size(); ++i) {
        cout << left << setw(5) << i + 1
             << setw(50) << selectedTitles[i]
             << selectedGenres[i] << endl;
    }
    cout << endl;
}

// Function to update weights for all genres using the Hedge algorithm
void updateWeights(vector<double>& weights, const vector<double>& rewards) {
    for (int i = 0; i < weights.size(); ++i) {
        double loss = 1 - rewards[i];
        weights[i] *= exp(-learningRate * loss); // Update weight using exponential loss
    }
    // Normalize weights
    double totalWeight = accumulate(weights.begin(), weights.end(), 0.0);
    for (double& weight : weights) {
        weight /= totalWeight;
    }
}

int main() {
    srand(time(0)); // Seed random number generator

    map<string, vector<string>> titles;
    vector<string> genres;
    loadDataset("Interesting_Video_Dataset_for_Demo.csv", titles, genres);
    int numGenres = genres.size();

    vector<double> weights = initializeWeights(numGenres);
    string dataFile = "round_data.csv"; 

    for (int round = 1; round <= numRounds; ++round) {
        cout << "\n=== Round " << round << " ===\n";

        // Select 10 videos based on current weights
        vector<string> selectedTitles;
        vector<string> selectedGenres;

        for (int i = 0; i < 10; ++i) {
            int selectedGenre = selectGenre(weights);
            string genre = genres[selectedGenre];
            string video = titles[genre][rand() % titles[genre].size()];

            selectedTitles.push_back(video);
            selectedGenres.push_back(genre);
        }

        // Display recommendations in tabular format
        displayRecommendations(selectedTitles, selectedGenres);

        // Simulate user engagement
        cout << "Select videos by number (comma-separated, e.g., 1,3): ";
        string input;
        getline(cin, input);
        stringstream ss(input);
        string token;
        vector<int> engagedIndices;

        while (getline(ss, token, ',')) {
            engagedIndices.push_back(stoi(token) - 1);
        }

        // Calculate rewards for all genres
        vector<double> rewards(numGenres, 0.0);
        for (int idx : engagedIndices) {
            for (int i = 0; i < numGenres; ++i) {
                if (genres[i] == selectedGenres[idx]) {
                    rewards[i] = 1.0;
                }
            }
        }

        updateWeights(weights, rewards);

        saveRoundData(dataFile, genres, weights, round);

        double totalWeight = accumulate(weights.begin(), weights.end(), 0.0);
        cout << "\nUpdated Genre Probabilities:\n";
        for (int i = 0; i < numGenres; ++i) {
            cout << genres[i] << ": " << (weights[i] / totalWeight) << "\n";
        }
    }

    // Final user preferences display
    vector<tuple<string, double>> genrePreferences;
    double totalWeight = accumulate(weights.begin(), weights.end(), 0.0);

    for (int i = 0; i < numGenres; ++i) {
        genrePreferences.emplace_back(genres[i], weights[i] / totalWeight);
    }

    // Sort preferences by weights in descending order
    sort(genrePreferences.begin(), genrePreferences.end(), [](const auto& a, const auto& b) {
        return get<1>(a) > get<1>(b); 
    });

    // Display final user preferences
    cout << "====================================================================";
    cout << "\nBased on your CHOICES, below are your preferences:\n";
    cout << left << setw(20) << "Genre" << "Final Weight" << endl;
    cout << string(30, '-') << endl;
    for (const auto& [genre, weight] : genrePreferences) {
        cout << left << setw(20) << genre << weight << endl;
    }

    return 0;
}
