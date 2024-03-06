import spacy
from collections import Counter
from who.preprocessing_who import preprocess_who

# Load spaCy model for English
nlp = spacy.load("en_core_web_lg")

def extract_person_entities(text):
    """
    Extracts person entities from the given text using spaCy NER.

    Args:
    text (str): The preprocessed text from which to extract person entities.

    Returns:
    list: A list of extracted person entities (as strings).
    """
    doc = nlp(text)
    return [ent.text for ent in doc.ents if ent.label_ == 'PERSON']

THERAPIST_REFERENCES = ['dr', 'doctor', 'therapist', 'counselor']

def is_therapist_reference(entity):
    """
    Determines if the given entity is a reference to the therapist.

    Args:
    entity (str): The entity to check.

    Returns:
    bool: True if the entity is a reference to the therapist, False otherwise.
    """
    return any(ref in entity.lower() for ref in THERAPIST_REFERENCES)

def find_most_relevant_entity(entities):
    """
    Identifies the most relevant person entity based on frequency.

    Args:
    entities (list): A list of person entities.

    Returns:
    str: The most relevant person entity.
    """
    if not entities:
        return None

    # Count the frequency of each entity
    frequency = Counter(entities)
    most_common = frequency.most_common(1)
    return most_common[0][0]  # Return the entity with the highest frequency

def extract_most_relevant_person(text):
    """
    Extracts the most relevant 'Who' from the conversation text.

    Args:
    text (str): The raw conversation text.

    Returns:
    str: The most relevant 'Who' entity.
    """
    preprocessed_text = preprocess_who(text)
    person_entities = extract_person_entities(preprocessed_text)

    # Filter out therapist references and prioritize other names
    filtered_entities = [entity for entity in person_entities if not is_therapist_reference(entity)]

    person = find_most_relevant_entity(filtered_entities)
    if person:
        return person
    
    # If no person is mentioned during the conversation
    return "User"
