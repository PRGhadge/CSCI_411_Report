# README

This repository contains the implementation of the Hedge Algorithm for personalized content recommendation and related test cases.

---

## Directory Structure

### `Code with Defined Rounds`
Contains a program (`hedgeExperimental.cpp`) designed to measure execution time for a fixed number of rounds.

- **Files**:
  - `hedgeExperimental.cpp`: Code to run the hedge algorithm for a fixed number of rounds.
  - `weights.csv`: Output file storing normalized weights after all rounds.

**To Compile and Run**:
```bash
cd "Code with Defined Rounds"
g++ -o hedge hedgeExperimental.cpp
./hedge
```

### `Code with Test Cases`
Contains the implementation of the Hedge Algorithm (`hedgeAlgorithmTests.cpp`) with predefined input and output test cases.

- **Files**:
  - `hedgeAlgorithmTests.cpp`: Implementation of the Hedge Algorithm with test case inputs.
  - `Test Cases.txt`: A text file listing inputs and expected outputs for various test cases.

**To Compile and Run**:
```bash
cd "Code with Test Cases"
g++ -o test hedgeAlgorithmTests.cpp
./test
```

You will be prompted to input the following during runtime:
1. **Number of genres**: Total number of content genres.
2. **Number of rounds**: Total iterations to simulate.
3. **Learning rate**: Learning rate used in the Hedge Algorithm.
4. **Genre names**: Space-separated list of genre names.
5. **Engagement probabilities**: Space-separated list of engagement probabilities (between 0 and 1).

**Example Input**:
```bash
Enter number of genres, number of rounds, and learning rate: 3 10 0.1
Enter genre names: Funny Pets Gaming
Enter engagement probabilities for each genre: 0.3 0.5 0.7
```

### `Demo code`
Contains a program (`userEngagementclassDemo.cpp`) designed for interactive demonstrations. Users can select videos from recommended lists to simulate personalized engagement.

- **Files**:
  - `userEngagementclassDemo.cpp`: Main implementation for the demo.
  - `Interesting_Video_Dataset_for_Demo.csv`: Input dataset of video titles and their associated genres.
  - `plot.py`: Python script for visualizing genre weights over rounds.
  - `round_data.csv`: Output CSV storing weights across rounds.
  - `final_weights_highlighted_bar.png`: Bar chart of final weights.
  - `weights_highlighted_trend.png`: Line plot highlighting weight trends across rounds.

**To Compile and Run**:
```bash
cd "Demo code"
g++ -o demo userEngagementclassDemo.cpp
./demo
```
You will be prompted to:
1. **Select videos**: Simulate user engagement by selecting videos based on their numbers.
2. View the updated genre probabilities after each round.

**To Visualize Results**:
Ensure `round_data.csv` is generated after running the demo.
```bash
python plot.py
```
This script generates the following visualizations:
- **Final Weights Bar Chart**: `final_weights_highlighted_bar.png`
- **Weight Trends Across Rounds**: `weights_highlighted_trend.png`

---

## Sample Commands

### Run Fixed Rounds Program
```bash
cd "Code with Defined Rounds"
g++ -o hedge hedgeExperimental.cpp
./hedge
```

### Run Test Cases
```bash
cd "Code with Test Cases"
g++ -o test hedgeAlgorithmTests.cpp
./test
```

### Run Demo and Visualize Results
```bash
cd "Demo code"
g++ -o demo userEngagementclassDemo.cpp
./demo
python plot.py
```

---

## Notes
- **Random Seed**: The random seed is fixed in the demo to ensure reproducibility.
- **CSV Format**: Input dataset must follow the format of `Interesting_Video_Dataset_for_Demo.csv`.
- Ensure Python and Matplotlib are installed to run the visualization script.
