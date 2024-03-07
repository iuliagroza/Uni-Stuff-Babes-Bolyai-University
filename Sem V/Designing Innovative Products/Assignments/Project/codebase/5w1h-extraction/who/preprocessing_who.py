import re
import spacy

# Load spaCy model
nlp = spacy.load("en_core_web_lg")

def preprocess_who(text):
    """
    Performs preprocessing on the text specifically for "Who?" extraction in conversational data.

    Args:
    text (str): The input text from the conversation.

    Returns:
    str: Preprocessed text.
    """
    # Normalize Unicode characters
    text = text.encode('ascii', 'ignore').decode('ascii')

    # Expand contractions
    contractions = {
        "can't": "cannot", "won't": "will not", "n't": " not",
        "'re": " are", "'s": " is", "'d": " would",
        "'ll": " will", "'ve": " have", "'m": " am"
    }
    contractions_re = re.compile('(%s)' % '|'.join(contractions.keys()))
    def expand_contractions(s, contractions_dict=contractions):
        return contractions_re.sub(lambda match: contractions_dict[match.group(0)], s)
    text = expand_contractions(text)

    # Remove excessive whitespaces
    text = ' '.join(text.split())

    # Handling special characters and punctuations
    punctuation = '!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~'
    text = text.translate(str.maketrans('', '', punctuation))

    return text