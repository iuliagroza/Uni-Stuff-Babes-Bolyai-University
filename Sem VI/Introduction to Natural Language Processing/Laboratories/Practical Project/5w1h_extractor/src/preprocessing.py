import spacy
import json
from logger_config import setup_logger

logger = setup_logger('preprocessing', 'preprocessing.log')

def load_model():
    logger.info('Loading model')
    return spacy.load("ro_core_news_lg")

def preprocess_text(nlp, text):
    doc = nlp(text)
    return doc

def extract_sentences(doc):
    return [sent.text for sent in doc.sents]

def read_dataset(file_path):
    logger.info(f'Reading dataset from {file_path}')
    with open(file_path, 'r', encoding='utf-8') as f:
        dataset = json.load(f)
    return dataset

def preprocess_dataset(dataset):
    nlp = load_model()
    preprocessed_data = []
    for entry in dataset:
        text = entry.get("text", "")
        if not text:
            sentences = entry.get("sentences", [])
            text = " ".join(sentences)
        doc = preprocess_text(nlp, text)
        sentences = extract_sentences(doc)
        preprocessed_data.append({
            "title": entry.get("title", ""),
            "text": text,
            "sentences": sentences,
            "summary": entry.get("summary", ""),
            "true_why_clauses": entry.get("true_why_clauses", []),
            "true_how_clauses": entry.get("true_how_clauses", [])
        })
    logger.info(f'Preprocessed {len(preprocessed_data)} entries')
    return preprocessed_data

if __name__ == "__main__":
    dataset_file_path = "data/test.json"
    dataset = read_dataset(dataset_file_path)
    preprocessed_data = preprocess_dataset(dataset)

    for entry in preprocessed_data:
        logger.info(f"Title: {entry['title']}")
        for sentence in entry['sentences']:
            logger.info(f"  - {sentence}")
        logger.info(f"Summary: {entry['summary']}")
