import numpy as np

# 1. Setup Data
# ------------------------------------------
np.random.seed(42) # Ensures consistent results

# Input data (Hours studied, Hours slept)
X = np.array(([2, 9], [1, 5], [3, 6]), dtype=float)
X = X / np.amax(X, axis=0) # Normalize input to 0-1 range

# Target data (Test Score)
y = np.array(([92], [86], [89]), dtype=float)
y = y / 100.0  # CRITICAL FIX: Normalize output to 0-1 so Sigmoid can predict it

# 2. Define Helper Functions
# ------------------------------------------
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def sigmoid_derivative(x):
    return x * (1 - x)

# 3. Initialize Weights and Biases
# ------------------------------------------
input_neurons = 2
hidden_neurons = 3
output_neurons = 1

# Random weights and biases
weights_input_hidden  = np.random.uniform(size=(input_neurons, hidden_neurons))
bias_hidden           = np.random.uniform(size=(1, hidden_neurons))

weights_hidden_output = np.random.uniform(size=(hidden_neurons, output_neurons))
bias_output           = np.random.uniform(size=(1, output_neurons))

learning_rate = 0.1
epochs = 7000

# 4. Training Loop
# ------------------------------------------
for i in range(epochs):
    
    # --- Forward Propagation (Guessing) ---
    # Input -> Hidden Layer
    hidden_input = np.dot(X, weights_input_hidden) + bias_hidden
    hidden_output = sigmoid(hidden_input)
    
    # Hidden -> Output Layer
    final_input = np.dot(hidden_output, weights_hidden_output) + bias_output
    predicted_output = sigmoid(final_input)
    
    # --- Backward Propagation (Learning) ---
    # Calculate Error
    error = y - predicted_output
    
    # Calculate changes for Output Layer
    d_output = error * sigmoid_derivative(predicted_output)
    
    # Calculate changes for Hidden Layer
    error_hidden_layer = d_output.dot(weights_hidden_output.T)
    d_hidden = error_hidden_layer * sigmoid_derivative(hidden_output)
    
    # Update Weights and Biases
    weights_hidden_output += hidden_output.T.dot(d_output) * learning_rate
    bias_output           += np.sum(d_output, axis=0, keepdims=True) * learning_rate
    
    weights_input_hidden  += X.T.dot(d_hidden) * learning_rate
    bias_hidden           += np.sum(d_hidden, axis=0, keepdims=True) * learning_rate

# 5. Final Result
# ------------------------------------------
print("Target Output:\n", y)
print("Predicted Output:\n", predicted_output)