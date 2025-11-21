import pandas as pd
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn import metrics

# 1. Load Data (Assuming Iris Dataset structure)
names = ['sepal-length', 'sepal-width', 'petal-length', 'petal-width', 'Class']
dataset = pd.read_csv("AIML/datasets/p5.csv", names=names) # Added names argument for safety

X = dataset.iloc[:, :-1]
y = dataset.iloc[:, -1]

# 2. Split with Seed (random_state ensures the split is the same every time)
Xtrain, Xtest, ytrain, ytest = train_test_split(X, y, test_size=0.10, random_state=42)

# 3. Train Model
classifier = KNeighborsClassifier(n_neighbors=5).fit(Xtrain, ytrain)
ypred = classifier.predict(Xtest)

# 4. Simplified Loop using zip() and f-strings
print(f"{'Original Label':<25} {'Predicted Label':<25} {'Correct/Wrong'}")
print("-" * 65)

for actual, predicted in zip(ytest, ypred):
    status = "Correct" if actual == predicted else "Wrong"
    print(f"{actual:<25} {predicted:<25} {status}")

# 5. Metrics
print("\nConfusion Matrix:\n", metrics.confusion_matrix(ytest, ypred))
print("\nClassification Report:\n", metrics.classification_report(ytest, ypred))
print(f"Accuracy: {metrics.accuracy_score(ytest, ypred):.2f}")