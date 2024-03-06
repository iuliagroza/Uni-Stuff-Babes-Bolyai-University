import numpy as np
import spacy
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.decomposition import NMF  # Non-Negative Matrix Factorization
from what.preprocessing_what import preprocess_what

nlp = spacy.load("en_core_web_lg")

def extract_significant_phrases(doc):
    """
    Extracts significant phrases from the SpaCy document.
    
    Args:
    doc (spacy.tokens.Doc): Processed SpaCy document.

    Returns:
    list: A list of significant phrases.
    """
    phrases = []
    for chunk in doc.noun_chunks:
        # Filter out short phrases and common words
        if len(chunk) > 1 and not all(token.is_stop for token in chunk):
            phrases.append(chunk.text.lower())
    return phrases

def perform_topic_modeling(phrases):
    """
    Performs topic modeling on the extracted phrases and identifies the most relevant phrase.

    Args:
    phrases (list): List of extracted phrases.

    Returns:
    str: The most relevant phrase.
    """
    vectorizer = TfidfVectorizer(min_df=0.01, max_df=0.75, stop_words='english', ngram_range=(1, 3))
    X = vectorizer.fit_transform(phrases)

    # Use NMF to find the dominant topic
    nmf = NMF(n_components=1, random_state=1).fit(X)

    # Get the topic distribution for phrases
    topic_distribution = nmf.transform(X)

    # Identify the phrase with the highest contribution to the dominant topic
    most_relevant_phrase_index = np.argmax(topic_distribution[:, 0])
    return phrases[most_relevant_phrase_index]

def extract_most_relevant_topic(conversation_text):
    preprocessed_text = preprocess_what(conversation_text)
    doc = nlp(preprocessed_text)
    significant_phrases = extract_significant_phrases(doc)
    topic = perform_topic_modeling(significant_phrases)
    return topic
