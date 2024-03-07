import spacy
from nltk.sentiment import SentimentIntensityAnalyzer

nlp = spacy.load("en_core_web_lg")
sia = SentimentIntensityAnalyzer()

REASON_KEYWORDS = ["because", "due to", "as a result", "the reason is", "since", "owing to", "caused by", "leads to"]

def extract_reason_context(sent, keyword):
    """
    Extracts broader context around the keyword in the sentence.
    """
    context = []
    for token in sent:
        if token.lemma_ in keyword:
            context = [str(tok) for tok in sent if not tok.is_punct]
            break
    return ' '.join(context)

def analyze_reasons(doc):
    """
    Analyzes sentences in the document to extract reasons.
    """
    reasons = []
    for sent in doc.sents:
        for keyword in REASON_KEYWORDS:
            if keyword in sent.text.lower():
                reason_context = extract_reason_context(sent, keyword)
                if reason_context:
                    reasons.append(reason_context)
    return reasons

def get_reason_relevance(reason):
    """
    Calculates the relevance of a reason based on sentiment and length.
    """
    sentiment_score = sia.polarity_scores(reason)['compound']
    length_score = len(reason.split())  # Longer reasons might be more descriptive
    return sentiment_score + length_score

def extract_most_relevant_reason(text):
    doc = nlp(text)
    reasons = analyze_reasons(doc)
    if not reasons:
        return 'No reason provided'
    
    scored_reasons = {reason: get_reason_relevance(reason) for reason in reasons}
    return max(scored_reasons, key=scored_reasons.get, default=None)
