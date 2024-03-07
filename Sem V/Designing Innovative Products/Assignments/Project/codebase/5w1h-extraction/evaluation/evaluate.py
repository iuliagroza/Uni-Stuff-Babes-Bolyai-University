import evaluate_who
import evaluate_what
import evaluate_when
import evaluate_where
import evaluate_why
import evaluate_how

def run_evaluation():
    # Dictionary to store results
    results = {
        'who': None,
        'what': None,
        'when': None,
        'where': None,
        'why': None,
        'how': None
    }

    dataset_path = 'common_utils/transformed_dataset.csv'
    # Run each evaluation and store the results
    results['who'] = evaluate_who.main(dataset_path=dataset_path)
    results['what'] = evaluate_what.main(dataset_path=dataset_path)
    results['when'] = evaluate_when.main(dataset_path=dataset_path)
    results['where'] = evaluate_where.main(dataset_path=dataset_path)
    results['why'] = evaluate_why.main(dataset_path=dataset_path)
    results['how'] = evaluate_how.main(dataset_path=dataset_path)

    # Calculate the average of each metric
    avg_precision = sum(r[0] for r in results.values() if r) / len(results)
    avg_recall = sum(r[1] for r in results.values() if r) / len(results)
    avg_f1 = sum(r[2] for r in results.values() if r) / len(results)

    return avg_precision, avg_recall, avg_f1

if __name__ == "__main__":
    precision, recall, f1 = run_evaluation()
    print(f"Average Precision: {precision:.2f}")
    print(f"Average Recall: {recall:.2f}")
    print(f"Average F1 Score: {f1:.2f}")