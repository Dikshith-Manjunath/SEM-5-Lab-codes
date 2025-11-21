import numpy as np
import pandas as pd

# Load dataset
data = pd.read_csv('AIML/datasets/p3.csv')
print("Dataset:\n", data)

# attributes = all attributes except last column
attributes = np.array(data)[:, :-1]
target = np.array(data)[:, -1]

print("\nattributes:\n", attributes)
print("\nTarget:\n", target)

# --------------------------------------------------
# Candidate Elimination Algorithm
# --------------------------------------------------
def learn(attributes, target):
    # Step 1: Initialize S and G
    specific_h = attributes[0].copy()
    general_h = [["?" for i in range(len(specific_h))] for i in range(len(specific_h))]

    print("\nInitial Specific Hypothesis:", specific_h)
    print("Initial General Hypothesis:", general_h)

    # Step 2: Process training examples
    for i, value in enumerate(attributes):
        print(f"\nvalue {i+1}: {value}, Target: {target[i]}")

        if target[i] == "Yes":   # Positive example
            print(" → Positive example")
            # Generalize S where necessary
            for x in range(len(specific_h)):
                if value[x] != specific_h[x]:
                    specific_h[x] = "?"
                    general_h[x][x] = "?"
        else:                   # Negative example
            print(" → Negative example")
            # Specialize G to exclude this value
            for x in range(len(specific_h)):
                if value[x] != specific_h[x]:
                    general_h[x][x] = specific_h[x]
                else:
                    general_h[x][x] = "?"

        print("Updated Specific Hypothesis:", specific_h)
        print("Updated General Hypothesis:", general_h)

    # Remove fully '?' rows from G
    general_h = [g for g in general_h if g != ["?"] * len(specific_h)]

    return specific_h, general_h


# Run CE Algorithm
S_final, G_final = learn(attributes, target)

print("\nFinal Specific Hypothesis:\n", S_final)
print("\nFinal General Hypothesis:\n", G_final)
