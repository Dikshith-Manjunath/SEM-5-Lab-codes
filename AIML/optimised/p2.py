import pandas as pd
import numpy as np

# -------------------------------------
# Load dataset
# -------------------------------------
data = pd.read_csv("C:/Users/ISE14/Documents/CSV_AIML/P2Data.csv")
print("Dataset:\n", data)

# Convert dataset into numpy arrays
attributes = np.array(data)[:, :-1]   # all columns except last
targets = np.array(data)[:, -1]       # last column (Yes/No)

print("\nAttributes:\n", attributes)
print("\nTargets: ", targets)

# -------------------------------------
# Find-S Algorithm
# -------------------------------------
def train_find_s(attributes, targets):
    # Step 1: Find the first positive example to initialize the specific hypothesis
    specific_h = None

    for i, value in enumerate(targets):
        if value == "Yes":
            specific_h = attributes[i].copy()
            break

    # Step 2: Generalize hypothesis for every other positive example
    for i, value in enumerate(targets):
        if value == "Yes":
            for j in range(len(specific_h)):
                if attributes[i][j] != specific_h[j]:
                    specific_h[j] = "?"

    return specific_h


# -------------------------------------
# Output final hypothesis
# -------------------------------------
final_hypothesis = train_find_s(attributes, targets)
print("\nFinal Hypothesis:", final_hypothesis)
