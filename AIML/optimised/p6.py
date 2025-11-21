import numpy as np
import pandas as pd
from pgmpy.models import DiscreteBayesianNetwork
from pgmpy.estimators import MaximumLikelihoodEstimator
from pgmpy.inference import VariableElimination

# 1. Load Data
heartDisease = pd.read_csv("AIML/datasets/p6.csv")

# 2. Data Cleaning
# Replace '?' with NaN and drop rows with missing values
heartDisease = heartDisease.replace('?', np.nan).dropna()

# Ensure columns match what the model expects (renaming if necessary)
# If you downloaded the real dataset, you might need to uncomment the line below:
# heartDisease.rename(columns={'sex': 'gender', 'target': 'Heartdisease'}, inplace=True)

print('Few examples from the dataset are given below')
print(heartDisease.head())

# 3. Define the Model (DAG - Directed Acyclic Graph)
# This structure defines the dependencies (e.g., Age influences Heart Disease)
model = DiscreteBayesianNetwork([
    ('age', 'Heartdisease'),
    ('gender', 'Heartdisease'),
    ('exang', 'Heartdisease'),
    ('cp', 'Heartdisease'),
    ('Heartdisease', 'restecg'),
    ('Heartdisease', 'chol')
])

# 4. Train the Model
print('\nLearning CPD using Maximum Likelihood Estimators...')
model.fit(heartDisease, estimator=MaximumLikelihoodEstimator)

# 5. Inference
print('\nInferencing with Bayesian Network:')
HeartDiseasetest_infer = VariableElimination(model)

print('\n1. Probability of HeartDisease given evidence: age=35')
q1 = HeartDiseasetest_infer.query(
    variables=['Heartdisease'],
    evidence={'age': 35}
)
print(q1)

print('\n2. Probability of HeartDisease given evidence: chol=250')
q2 = HeartDiseasetest_infer.query(
    variables=['Heartdisease'],
    evidence={'chol': 259}
)
print(q2)