from sklearn.metrics import precision_score, recall_score, f1_score, classification_report
from preprocessing import load_model, preprocess_text, read_dataset, preprocess_dataset
from extract import extract_why, extract_how, log_dependency_relations
from logger_config import setup_logger

logger = setup_logger('evaluate', 'evaluate.log')

def evaluate_extraction(true_labels, predicted_labels):
    if not true_labels and not predicted_labels:
        return 0, 0, 0

    all_labels = list(set(true_labels + predicted_labels))
    y_true = [1 if label in true_labels else 0 for label in all_labels]
    y_pred = [1 if label in predicted_labels else 0 for label in all_labels]

    precision = precision_score(y_true, y_pred, zero_division=0)
    recall = recall_score(y_true, y_pred, zero_division=0)
    f1 = f1_score(y_true, y_pred, zero_division=0)

    report = classification_report(y_true, y_pred, zero_division=0)
    logger.info(f'Classification Report:\n{report}')

    return precision, recall, f1

def evaluate_entry(entry, nlp):
    if "text" not in entry:
        logger.error(f"Entry does not contain 'text' field: {entry}")
        return (None, None, None), (None, None, None)

    text = entry["text"]
    true_why_clauses = entry.get("true_why_clauses", [])
    true_how_clauses = entry.get("true_how_clauses", [])

    doc = preprocess_text(nlp, text)

    log_dependency_relations(doc)
    
    why_clauses = extract_why(doc)
    how_clauses = extract_how(doc)
    
    logger.info(f"Extracted Why Clauses: {why_clauses}")
    logger.info(f"Extracted How Clauses: {how_clauses}")

    why_precision, why_recall, why_f1 = evaluate_extraction(true_why_clauses, why_clauses)
    how_precision, how_recall, how_f1 = evaluate_extraction(true_how_clauses, how_clauses)

    return (why_precision, why_recall, why_f1), (how_precision, how_recall, how_f1)

def evaluate_dataset(dataset_file_path):
    logger.info(f'Evaluating dataset from {dataset_file_path}')
    dataset = read_dataset(dataset_file_path)
    preprocessed_data = preprocess_dataset(dataset)
    nlp = load_model()

    for entry in preprocessed_data:
        (why_metrics, how_metrics) = evaluate_entry(entry, nlp)
        if all(metric is not None for metric in why_metrics):
            why_precision, why_recall, why_f1 = why_metrics
            logger.info(f"Evaluation for Why Clauses - Precision: {why_precision:.2f}, Recall: {why_recall:.2f}, F1-score: {why_f1:.2f}")
        if all(metric is not None for metric in how_metrics):
            how_precision, how_recall, how_f1 = how_metrics
            logger.info(f"Evaluation for How Clauses - Precision: {how_precision:.2f}, Recall: {how_recall:.2f}, F1-score: {how_f1:.2f}")

if __name__ == "__main__":
    dataset_file_path = "data/test.json"
    evaluate_dataset(dataset_file_path)
