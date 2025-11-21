from sklearn.cluster import KMeans
from sklearn.mixture import GaussianMixture
from sklearn import metrics
import pandas as pd
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
matplotlib.use('QtAgg')

# --------------------------------------------
# 1. LOAD DATA
# --------------------------------------------
data = pd.read_csv("AIML/datasets/p8.csv")

# FIXED: Use .iloc for DataFrame slicing
# We keep X as a DataFrame so we can access columns by name (X.Petal_Length)
X = data.iloc[:, :-1]

# Convert iris labels to numbers manually to match color map
label_map = {
    'setosa': 0,
    'versicolor': 1,
    'virginica': 2
}
# Note: If your CSV uses "Iris-setosa", change keys above accordingly.
# The generator above uses "setosa", "versicolor", "virginica".
y_true = np.array([label_map[label] for label in data.iloc[:, -1]])

# Colors: 0=Red, 1=Lime, 2=Black
colors = np.array(['red', 'lime', 'black'])

plt.figure(figsize=(15, 5))

# --------------------------------------------
# 2. REAL LABELS PLOT
# --------------------------------------------
plt.subplot(1, 3, 1)
plt.title("Actual Labels")
plt.scatter(X.Petal_Length, X.Petal_Width, c=colors[y_true])

# --------------------------------------------
# 3. K-MEANS CLUSTERING
# --------------------------------------------
# random_state=42 acts as your "seed" for reproducible results
kmeans = KMeans(n_clusters=3, random_state=42)
kmeans_labels = kmeans.fit_predict(X)

plt.subplot(1, 3, 2)
plt.title("K-Means Clustering")
plt.scatter(X.Petal_Length, X.Petal_Width, c=colors[kmeans_labels])

print("K-Means Accuracy:", metrics.accuracy_score(y_true, kmeans_labels))
print("K-Means Confusion Matrix:\n", metrics.confusion_matrix(y_true, kmeans_labels))

# --------------------------------------------
# 4. GMM (EM) CLUSTERING
# --------------------------------------------
gmm = GaussianMixture(n_components=3, random_state=42)
gmm_labels = gmm.fit_predict(X)

plt.subplot(1, 3, 3)
plt.title("GMM (EM) Clustering")
plt.scatter(X.Petal_Length, X.Petal_Width, c=colors[gmm_labels])

print("GMM Accuracy:", metrics.accuracy_score(y_true, gmm_labels))
print("GMM Confusion Matrix:\n", metrics.confusion_matrix(y_true, gmm_labels))

plt.tight_layout()
plt.show()