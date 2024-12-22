import pandas as pd
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.pipeline import make_pipeline
from sklearn import metrics

# Sample text data with categories
data = {
    'text': [
        'The new iPhone was released last month.',
        'Manchester United won the game yesterday.',
        'Scientists discovered a new exoplanet.',
        'The stock market went up today.',
        'Learn how to cook Italian pasta.',
        'Python programming is fun and powerful.'
    ],
    'category': [
        'technology',
        'sports',
        'science',
        'business',
        'cooking',
        'technology'
    ]
}

# Convert data to a DataFrame
df = pd.DataFrame(data)

# Split data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(df['text'], df['category'], test_size=0.3, random_state=42)

# Create a pipeline with TfidfVectorizer and LogisticRegression model
model = make_pipeline(TfidfVectorizer(), LogisticRegression(max_iter=1000))

# Train the model
model.fit(X_train, y_train)

# Predict the category of the test set
predicted = model.predict(X_test)

# Evaluate the model
print("Accuracy:", metrics.accuracy_score(y_test, predicted))
print("\nClassification Report:\n", metrics.classification_report(y_test, predicted))

# Example prediction
example_text = ["How to bake a cake", "New AI model beats human performance"]
predicted_category = model.predict(example_text)
print("\nPredicted Categories for Example Texts:", predicted_category)

