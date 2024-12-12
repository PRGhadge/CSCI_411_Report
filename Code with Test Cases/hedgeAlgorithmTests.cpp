#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <iomanip> 

using namespace std;

// Initialize equal weights for all genres
vector<double> initializeWeights(int numGenres) {
    return vector<double>(numGenres, 1.0);
}

// Select a genre based on current weight distribution
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

// Update weights for all genres using the Hedge Algorithm
void updateWeights(vector<double>& weights, const vector<double>& rewards, double learningRate) {
    for (int i = 0; i < weights.size(); ++i) {
        double loss = 1 - rewards[i];
        weights[i] *= exp(-learningRate * loss);
    }

    // Normalize weights after updating
    double totalWeight = accumulate(weights.begin(), weights.end(), 0.0);
    for (double& weight : weights) {
        weight /= totalWeight;
    }
}

int main() {
    srand(42); // Fix random seed for reproducibility

    int numGenres, numRounds;
    double learningRate;
    cout << "Enter number of genres, number of rounds, and learning rate: ";
    cin >> numGenres >> numRounds >> learningRate;

    vector<string> genres(numGenres);
    cout << "Enter genre names: ";
    for (int i = 0; i < numGenres; ++i) {
        cin >> genres[i];
    }

    vector<double> engagementProbabilities(numGenres);
    cout << "Enter engagement probabilities for each genre: ";
    for (int i = 0; i < numGenres; ++i) {
        cin >> engagementProbabilities[i];
    }

    vector<double> weights = initializeWeights(numGenres);

    // Simulate rounds
    for (int round = 1; round <= numRounds; ++round) {
        // Select a genre based on current weights
        int selectedGenre = selectGenre(weights);

        // Simulate reward for the selected genre
        double reward = (double)rand() / RAND_MAX <= engagementProbabilities[selectedGenre] ? 1.0 : 0.0;

        // Generate rewards for all genres
        vector<double> rewards(numGenres);
        for (int i = 0; i < numGenres; ++i) {
            rewards[i] = (i == selectedGenre) ? reward : engagementProbabilities[i];
        }

        // Update weights for all genres
        updateWeights(weights, rewards, learningRate);
    }

    // Output final weights
    cout << "\nFinal Genre Weights and Probabilities:\n";
    cout << left << setw(20) << "Genre" << "Probability" << endl;
    cout << string(30, '-') << endl;

    for (int i = 0; i < numGenres; ++i) {
        cout << left << setw(20) << genres[i] << weights[i] << endl;
    }

    return 0;
}
