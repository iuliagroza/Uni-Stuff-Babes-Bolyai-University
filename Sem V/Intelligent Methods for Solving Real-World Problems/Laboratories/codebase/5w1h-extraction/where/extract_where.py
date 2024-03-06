import spacy
from nltk.sentiment import SentimentIntensityAnalyzer

# Load spaCy NLP model and Sentiment Intensity Analyzer
nlp = spacy.load("en_core_web_lg")
sia = SentimentIntensityAnalyzer()

def extract_custom_locations(text):
    """
    Extracts custom location entities from the text.

    Args:
    text (str): The input text from which to extract custom locations.

    Returns:
    list: A list of extracted custom location entities.
    """
    custom_locations = ['office', 'workplace', 'school', 'home', 'beach', 'cafe', 'restaurant', 'street', 'town', 'city', 'party', 'event', 'conference', 'hospital', 'clinic']
    locations = []
    for location in custom_locations:
        if location in text:
            locations.append(location)
    return locations

def filter_inaccurate_locations(locations, text):
    """
    Filters out inaccurately tagged locations.

    Args:
    locations (list): The list of extracted location entities.
    text (str): The input text for context understanding.

    Returns:
    list: A list of filtered location entities.
    """
    inaccurate_locations = ['incident', "disagreement", "event", 'therapy', 'therapy center', 'the Wellness Therapy Center']
    return [loc for loc in locations if loc not in inaccurate_locations]

def is_key_term_near_location(sentence, location, who, what):
    """
    Checks if any key term is near the location mention in the sentence.

    Args:
    sentence (spacy.tokens.span.Span): A sentence from the spaCy document.
    location (str): The location entity to check.

    Returns:
    bool: True if a key term is near the location, otherwise False.
    """

    # The extracted "Who?" and "What?" tokens. This ensures the temporal
    # references are relative and relevant to our extraction and all
    # questions are co-dependent.
    KEY_TERMS = [who, what]

    # Iterate through each token in the sentence
    for token in sentence:
        if token.text.lower() == location.lower():
            for child in token.children:
                if child.lemma_ in KEY_TERMS:
                    return True
            for ancestor in token.ancestors:
                if ancestor.lemma_ in KEY_TERMS:
                    return True
    return False

def analyze_narrative_flow(doc, location):
    """
    Analyzes the significance of a location within the narrative flow of the conversation.

    Args:
    doc (spacy.tokens.Doc): Processed spaCy document.
    location (str): Location entity to analyze.

    Returns:
    float: A score indicating the significance of the location in the narrative flow.
    """
    narrative_score = 0
    for sent in doc.sents:
        if location in sent.text:
            # Check the position of the sentence in the document
            position = sent.start_char / len(doc.text)
            if position < 0.33:
                narrative_score += 1  # Early mention in the conversation
            elif position > 0.66:
                narrative_score += 2  # Later mention, potentially more relevant to current context
    return narrative_score

def analyze_location_relevance(doc, location, who, what):
    """
    Analyzes the relevance of a location based on context.

    Args:
    doc (spacy.tokens.Doc): Processed spaCy document.
    location (str): Location entity to analyze.

    Returns:
    float: A score indicating the relevance of the location.
    """
    relevance_score = 0
    for sent in doc.sents:
        if location in sent.text:
            # Frequency component (each mention counts)
            relevance_score += 1

            # Sentiment analysis component
            sentiment_score = sia.polarity_scores(sent.text)['compound']
            relevance_score += abs(sentiment_score)  # Absolute value to weigh any strong sentiment

            # Proximity to key terms
            if is_key_term_near_location(sent, location, who, what):
                relevance_score += 3  # Increase score for proximity to key terms

            # Narrative flow analysis
            narrative_score = analyze_narrative_flow(doc, location)
            relevance_score += narrative_score

    return relevance_score


def extract_most_relevant_location(text, who, what):
    """
    Extracts the most relevant location from the text.

    Args:
    text (str): The input text from which to extract the most relevant location.

    Returns:
    str: The most relevant location entity.
    """
    doc = nlp(text)
    locations = []
    location_scores = {}

    ner_locations = [ent.text for ent in doc.ents if ent.label_ in ['GPE', 'LOC', 'ORG', 'FAC']]
    custom_locations = extract_custom_locations(text)
    all_locations = ner_locations + custom_locations

    # Using syntactic patterns and contextual clues
    for token in doc:
        if token.text.lower() in ['at', 'in', 'to'] and token.head.pos_ in ['NOUN', 'PROPN']:
            potential_location = token.head.text
            if potential_location.lower() not in locations:
                locations.append(potential_location)

    # Filter out inaccurately tagged locations
    locations = filter_inaccurate_locations(all_locations, text)
    
    for location in locations:
        location_scores[location] = analyze_location_relevance(doc, location, who, what)

    if location_scores:
        # Return the location with the highest relevance score
        return max(location_scores, key=location_scores.get)
    else:
        return 'No location'
