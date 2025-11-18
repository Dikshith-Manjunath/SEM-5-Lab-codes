from sklearn.cluster import KMeans
from sklearn.mixture import GaussianMixture
from sklearn import metrics
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# --------------------------------------------
# 1. LOAD DATA
# --------------------------------------------
data = pd.read_csv("AIML/datasets/p8.csv")

# Input features (Petal length, Petal width)
X = data[:, :-1]

# Convert iris labels to numbers
label_map = {
    'Iris-setosa': 0,
    'Iris-versicolor': 1,
    'Iris-virginica': 2
}
y_true = np.array([label_map[label] for label in data.iloc[:, -1]])

# Colors for plotting
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
kmeans = KMeans(n_clusters=3, random_state=0)
kmeans_labels = kmeans.fit_predict(X)

plt.subplot(1, 3, 2)
plt.title("K-Means Clustering")
plt.scatter(X.Petal_Length, X.Petal_Width, c=colors[kmeans_labels])

print("K-Means Accuracy:", metrics.accuracy_score(y_true, kmeans_labels))
print("K-Means Confusion Matrix:\n", metrics.confusion_matrix(y_true, kmeans_labels))


# --------------------------------------------
# 4. GMM (EM) CLUSTERING
# --------------------------------------------
gmm = GaussianMixture(n_components=3, random_state=0)
gmm_labels = gmm.fit_predict(X)

plt.subplot(1, 3, 3)
plt.title("GMM (EM) Clustering")
plt.scatter(X.Petal_Length, X.Petal_Width, c=colors[gmm_labels])

print("GMM Accuracy:", metrics.accuracy_score(y_true, gmm_labels))
print("GMM Confusion Matrix:\n", metrics.confusion_matrix(y_true, gmm_labels))

plt.show()
