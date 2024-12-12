import pandas as pd
import matplotlib.pyplot as plt

# Load the round data from CSV
data = pd.read_csv('round_data.csv')

# Plot line chart with highlighting for the top genre in each round
plt.figure(figsize=(10, 6))

# Track the top genre in each round
for genre in data.columns[1:]:
    if genre == data.iloc[-1, 1:].idxmax():  # Highlight the genre with the highest final weight
        plt.plot(data['Round'], data[genre], marker='o', linewidth=3, label=f"{genre} (Top)", color='gold')
    else:
        plt.plot(data['Round'], data[genre], marker='o', linestyle='dotted', label=genre)

plt.title('Genre Weights Across Rounds (Top Genre Highlighted)')
plt.xlabel('Rounds')
plt.ylabel('Weights')
plt.legend(title='Genres', bbox_to_anchor=(1.05, 1), loc='upper left')
plt.grid(True)
plt.tight_layout()
plt.savefig('weights_highlighted_trend.png')  # Save as PNG
plt.show()

# Bar chart for the final round with top genre highlighted
plt.figure(figsize=(10, 6))
final_round = data.iloc[-1, 1:]  # Get the last row for all genres
colors = ['lightpink' if genre == final_round.idxmax() else 'skyblue' for genre in final_round.index]

final_round.plot(kind='bar', color=colors, title='Final Genre Weights (Top Genre Highlighted)')
plt.xlabel('Genres')
plt.ylabel('Weights')
plt.xticks(rotation=45)
plt.tight_layout()
plt.savefig('final_weights_highlighted_bar.png')  # Save as PNG
plt.show()
