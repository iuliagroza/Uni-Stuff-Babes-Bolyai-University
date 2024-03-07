import re
import spacy

# Load spaCy model
nlp = spacy.load("en_core_web_lg")

def preprocess_what(text):
    """
    Preprocesses the conversation text for "What?" extraction.

    Args:
    text (str): The conversation text.

    Returns:
    str: The preprocessed conversation text.
    """
    # Convert to lowercase for uniformity
    text = text.lower()

    # Remove unnecessary characters
    text = re.sub(r"[^a-zA-Z0-9\s]", " ", text)

    # Replace multiple spaces with a single space
    text = re.sub(r"\s+", " ", text).strip()

    # Remove specific words such as 'therapist'
    words_to_remove = ['therapist']
    return ' '.join([token.text for token in nlp(text) if token.text.lower() not in words_to_remove])