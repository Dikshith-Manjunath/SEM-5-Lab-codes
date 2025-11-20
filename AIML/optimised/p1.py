from math import sqrt

# ------------------------------
# Basic statistics
# ------------------------------

def mean(values):
    return sum(values) / len(values)

def variance(values, mean_value):
    return sum((v - mean_value)**2 for v in values) / len(values)

def covariance(xs, mean_x, ys, mean_y):
    return sum((xs[i] - mean_x) * (ys[i] - mean_y) for i in range(len(xs))) / len(xs)

# ------------------------------
# Linear Regression (b0 + b1*x)
# ------------------------------

def coefficients(dataset):
    # Split into X and Y
    X = [row[0] for row in dataset]
    Y = [row[1] for row in dataset]

    mean_x = mean(X)
    mean_y = mean(Y)

    b1 = covariance(X, mean_x, Y, mean_y) / variance(X, mean_x)
    b0 = mean_y - b1 * mean_x

    return b0, b1

def predict_row(x_value, b0, b1):
    return b0 + b1 * x_value

def simple_linear_regression(train_data, test_data):
    b0, b1 = coefficients(train_data)
    predictions = [predict_row(row[0], b0, b1) for row in test_data]
    return predictions

# ------------------------------
# Model Evaluation
# ------------------------------

def rmse_metric(actual, predicted):
    errors = [(predicted[i] - actual[i])**2 for i in range(len(actual))]
    return sqrt(sum(errors) / len(actual))

def evaluate_algorithm(dataset):
    # Copy dataset and blank out Y values in the test set
    test_set = [ [row[0]] for row in dataset ]

    predictions = simple_linear_regression(dataset, test_set)

    # Actual Y values
    actual_values = [row[1] for row in dataset]

    return rmse_metric(actual_values, predictions)

# ------------------------------
# Run sample
# ------------------------------

dataset = [
    [1, 1],
    [2, 3],
    [4, 3],
    [3, 2],
    [5, 5]
]

rmse = evaluate_algorithm(dataset)
b0, b1 = coefficients(dataset)

print("RMSE =", rmse)
print("b0 =", b0, "\nb1 =", b1)

#   winget install --id Git.Git -e --source winget