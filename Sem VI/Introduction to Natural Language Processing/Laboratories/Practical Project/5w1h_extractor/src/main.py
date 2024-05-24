from evaluate import evaluate_dataset
from logger_config import setup_logger

def main():
    logger = setup_logger('main', 'main.log')
    logger.info('Started main function')
    
    dataset_file_path = "data/test.json"
    
    evaluate_dataset(dataset_file_path)
    
    logger.info('Finished main function')

if __name__ == "__main__":
    main()
