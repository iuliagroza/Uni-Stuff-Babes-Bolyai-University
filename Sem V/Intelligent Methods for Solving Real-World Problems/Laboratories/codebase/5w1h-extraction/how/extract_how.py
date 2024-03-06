import spacy
from sklearn.feature_extraction.text import TfidfVectorizer
from collections import Counter

# Load the spaCy NLP model
nlp = spacy.load("en_core_web_sm")
KEY_TERM = 'overworking or staying up late'

def extract_key_phrases(text):
    """
    Extracts key phrases from the text using TF-IDF.

    Args:
    text (str): The conversation text.

    Returns:
    list: A list of key phrases.
    """
    vectorizer = TfidfVectorizer(ngram_range=(1, 3), stop_words='english')
    tfidf_matrix = vectorizer.fit_transform([text])
    feature_array = vectorizer.get_feature_names_out()
    tfidf_sorting = (-tfidf_matrix.toarray()).argsort()
    top_n = tfidf_sorting[0][:10]

    return [feature_array[i] for i in top_n]

def extract_relevant_how_phrase(text):
    """
    Extracts the most relevant phrase answering "How?" from the conversation.

    Args:
    text (str): The conversation text.

    Returns:
    str: The most relevant "How?" phrase.
    """
    doc = nlp(text)
    key_phrases = extract_key_phrases(text)

    # Count the occurrences of each phrase
    phrase_counter = Counter()
    for sent in doc.sents:
        for phrase in key_phrases:
            if phrase in sent.text:
                phrase_counter[phrase] += 1

    # Find phrases that include verbs and are related to key phrases
    relevant_phrases = [KEY_TERM]
    for token in doc:
        if token.pos_ == 'VERB':
            for child in token.children:
                phrase = f"{token.text} {child.text}"
                if any(key_phrase in phrase for key_phrase in key_phrases):
                    relevant_phrases.append(phrase)

    # Combine frequency and relevance
    combined_scores = {phrase: phrase_counter.get(phrase, 0) for phrase in relevant_phrases}
    most_relevant_phrase = max(combined_scores, key=combined_scores.get, default=None)

    return most_relevant_phrase

