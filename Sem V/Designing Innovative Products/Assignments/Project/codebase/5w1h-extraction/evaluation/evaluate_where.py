import pandas as pd
import sys
from pathlib import Path

# Get the absolute path of the parent directory
parent_dir = str(Path(__file__).resolve().parent.parent)
if parent_dir not in sys.path:
    sys.path.append(parent_dir)

from sklearn.metrics import precision_score, recall_score, f1_score
from where.extract_where import extract_most_relevant_location

def load_annotated_dataset(dataset_path):
    """
    Load the dataset with annotations from a CSV file.
    
    Args:
    dataset_path (str): The path to the dataset file.

    Returns:
    DataFrame: A pandas DataFrame containing the dataset.
    """
    return pd.read_csv(dataset_path)

def evaluate_performance(annotations, predictions):
    """
    Evaluates the performance of the entity extraction.

    Args:
    annotations (list): The list of true 'Who' entities.
    predictions (list): The list of predicted 'Who' entities.

    Returns:
    tuple: Precision, Recall, and F1 Score.
    """
    precision = precision_score(annotations, predictions, average='macro', zero_division=0)
    recall = recall_score(annotations, predictions, average='macro', zero_division=0)
    f1 = f1_score(annotations, predictions, average='macro', zero_division=0)

    return precision, recall, f1

def main(dataset_path):
    dataset = load_annotated_dataset(dataset_path)

    # Extracting predictions and annotations
    annotations, predictions = [], []
    for _, row in dataset.iterrows():
        text, true_entity = row['Text'], row['Where']
        who, what = row['Who'], row['What']
        predicted_entity = extract_most_relevant_location(text, who, what)
        annotations.append(true_entity)
        predictions.append(predicted_entity)

    # Calculating performance metrics
    precision, recall, f1 = evaluate_performance(annotations, predictions)

    print("Evaluation of \"Where?\" extraction:")
    print(f"Precision: {precision:.2f}")
    print(f"Recall: {recall:.2f}")
    print(f"F1 Score: {f1:.2f}")
    print()

if __name__ == "__main__":
    dataset_path = 'common_utils/transformed_dataset.csv'
    main(dataset_path)
