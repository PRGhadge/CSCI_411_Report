#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

const double learningRate = 0.1; 

// Initialize equal weights for all genres
vector<double> initializeWeights(int numGenres) {
    return vector<double>(numGenres, 1.0);
}

// Simulate binary reward for a genre
double getReward(double engagementProbability) {
    return ((double)rand() / RAND_MAX <= engagementProbability) ? 1.0 : 0.0;
}

// Update weights for all genres
void updateWeights(vector<double>& weights, const vector<double>& rewards, double learningRate) {
    for (int i = 0; i < weights.size(); ++i) {
        double loss = 1 - rewards[i]; // Compute loss for the genre
        weights[i] *= exp(-learningRate * loss); // Update weight using exponential loss
    }
    // Normalize weights
    double totalWeight = accumulate(weights.begin(), weights.end(), 0.0);
    for (double& weight : weights) {
        weight /= totalWeight;
    }
}

int main() {
    srand(time(0)); // Seed for reproducibility

    // Define genres and their engagement probabilities
    vector<string> genres = {"Funny", "Motivational", "Sad", "Pets", "Gaming"};
    vector<double> engagementProbabilities = {0.2, 0.7, 0.5, 0.9, 0.6};
    vector<double> newEngagementProbabilities = {0.5, 0.4, 0.7, 0.3, 0.8};
    vector<int> rounds = {100, 500, 1000, 5000, 10000, 50000, 100000};

    // Open a file to log normalized weights
    ofstream outFile("weights.csv");
    outFile << "Round";
    for (const auto& genre : genres) outFile << "," << genre;
    outFile << "\n";

    // Run simulations for different numbers of rounds
    for (int numRounds : rounds) {
        cout << "Running simulation for " << numRounds << " rounds..." << endl;

        vector<double> weights = initializeWeights(genres.size());
        auto start = high_resolution_clock::now(); // Start timer

        for (int round = 1; round <= numRounds; ++round) {
            if (round == numRounds / 2) engagementProbabilities = newEngagementProbabilities;

            // Collect rewards for all genres
            vector<double> rewards(genres.size());
            for (int i = 0; i < genres.size(); ++i) {
                rewards[i] = getReward(engagementProbabilities[i]);
            }

            // Update weights for all genres
            updateWeights(weights, rewards, learningRate);
        }

        auto stop = high_resolution_clock::now(); // Stop timer
        auto duration = duration_cast<milliseconds>(stop - start);

        cout << "Execution time for " << numRounds << " rounds: " << duration.count() << " milliseconds." << endl;

        // Log final weights to file
        outFile << "Final Weights (" << numRounds << " rounds)";
        for (double weight : weights) outFile << "," << weight;
        outFile << "\n";
    }

    outFile.close();
    return 0;
}
