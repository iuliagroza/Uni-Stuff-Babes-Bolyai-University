from logger_config import setup_logger

logger = setup_logger('extract', 'extract.log')

def log_dependency_relations(doc):
    for sent in doc.sents:
        logger.info(f"Sentence: {sent.text}")
        for token in sent:
            logger.info(f"Token: {token.text}, Dep: {token.dep_}, Head: {token.head.text}, Children: {[child.text for child in token.children]}")

def extract_why(doc):
    why_clauses = []
    for sent in doc.sents:
        logger.info(f"Analyzing sentence: {sent.text}")
        for token in sent:
            logger.info(f"Token: {token.text}, Dep: {token.dep_}, Head: {token.head.text}")
            if token.dep_ in ["mark", "advcl", "obl"]:
                subtree_tokens = [t.text.lower() for t in token.subtree]
                logger.info(f"Subtree tokens: {subtree_tokens}")
                if any(phrase in subtree_tokens for phrase in ["din cauza", "datorită", "pentru că", "deoarece"]):
                    why_clauses.append(sent.text)
                    break
    logger.info(f'Extracted {len(why_clauses)} why clauses: {why_clauses}')
    return why_clauses

def extract_how(doc):
    how_clauses = []
    for sent in doc.sents:
        logger.info(f"Analyzing sentence: {sent.text}")
        for token in sent:
            logger.info(f"Token: {token.text}, Dep: {token.dep_}, Head: {token.head.text}")
            if token.dep_ in ["mark", "advcl", "obl"]:
                subtree_tokens = [t.text.lower() for t in token.subtree]
                logger.info(f"Subtree tokens: {subtree_tokens}")
                if any(phrase in subtree_tokens for phrase in ["prin", "în felul acesta", "astfel", "de această manieră"]):
                    how_clauses.append(sent.text)
                    break
    logger.info(f'Extracted {len(how_clauses)} how clauses: {how_clauses}')
    return how_clauses

if __name__ == "__main__":
    from preprocessing import load_model, preprocess_text, read_dataset, preprocess_dataset

    nlp = load_model()
    dataset_file_path = "data/test.json"
    dataset = read_dataset(dataset_file_path)
    preprocessed_data = preprocess_dataset(dataset)

    for entry in preprocessed_data:
        if 'text' not in entry:
            logger.error(f"Entry does not contain 'text' field: {entry}")
            continue
        
        logger.info(f"Title: {entry['title']}")
        doc = preprocess_text(nlp, " ".join(entry['sentences']))
        
        log_dependency_relations(doc)

        why_clauses = extract_why(doc)
        how_clauses = extract_how(doc)
        
        logger.info(f"Why Clauses: {why_clauses}")
        logger.info(f"How Clauses: {how_clauses}")
        logger.info(f"Summary: {entry['summary']}")
