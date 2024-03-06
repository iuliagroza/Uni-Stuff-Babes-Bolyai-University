import spacy

nlp = spacy.load("en_core_web_lg")

def preprocess_why(text):
    """
    Preprocesses the text for "Why?" extraction.

    Args:
    text (str): The text to preprocess.

    Returns:
    str: Preprocessed text.
    """
    doc = nlp(text.lower())  # Lowercasing and tokenization
    lemmatized_text = " ".join([token.lemma_ for token in doc if not token.is_punct and not token.is_space])
    return lemmatized_text