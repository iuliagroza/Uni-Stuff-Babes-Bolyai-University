import re
import string
import pandas as pd
import nltk
from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords
from nltk.stem import WordNetLemmatizer


# Ensure required NLTK resources are downloaded
nltk.download('punkt')
nltk.download('stopwords')
nltk.download('averaged_perceptron_tagger')
nltk.download('wordnet')


import re
import string

def clean_text(text):
    """
    Clean the text data, optimized for handling contractions.

    Args:
    text (str): The text to be cleaned.

    Returns:
    str: The cleaned text.
    """
    # Convert to lowercase
    text = text.lower()

    # Define contractions and their replacements
    contractions = {
        r"can't": "cannot",
        r"won't": "will not",
        r"n't": " not",
        r"'re": " are",
        r"'s": " is",
        r"'d": " would",
        r"'ll": " will",
        r"'ve": " have",
        r"'m": " am"
    }

    # Compile a regular expression pattern for contractions
    contractions_re = re.compile('(%s)' % '|'.join(contractions.keys()))

    # Function to replace contractions with full form
    def replace(match):
        return contractions[match.group(0)]

    # Apply the compiled regular expression to the text
    text = contractions_re.sub(replace, text)

    # Handling punctuation: Retain punctuation like '!', '?' for sentiment analysis
    # Remove other punctuation
    punct_to_retain = ':/!?'
    punct_to_remove = string.punctuation.replace(punct_to_retain, '')
    text = text.translate(str.maketrans('', '', punct_to_remove))

    # Remove extra spaces and newlines
    text = re.sub(r'\s+', ' ', text).strip()

    # Correcting common domain-specific typos or standardizing terms
    text = text.replace('therapyst', 'therapist')
    text = text.replace('geat', 'great')
    text = text.replace('stess', 'stress')
    text = text.replace('’', '\'')

    return text


def tokenize(text):
    # Tokenize the text into individual words
    return word_tokenize(text)


def remove_stop_words(tokens):
    # Remove common words that are not significant
    stop_words = set(stopwords.words('english', 'the', 'which', 'session', 'feel', 'think', 'um', 'uh', 'you know'))
    return [token for token in tokens if token not in stop_words]


def lemmatize(tokens):
    lemmatizer = WordNetLemmatizer()
    return [lemmatizer.lemmatize(token) for token in tokens]


def pos_tagging(tokens):
    return nltk.pos_tag(tokens)


def preprocess_data(file_path):
    try:
        # Try loading the dataset
        df = pd.read_csv(file_path, on_bad_lines='warn')

        # Apply the preprocessing functions
        df['Text'] = df['Text'].apply(clean_text)
        df['Tokens'] = df['Text'].apply(tokenize)
        df['Filtered_Tokens'] = df['Tokens'].apply(remove_stop_words)
        df['Lemmatized_Tokens'] = df['Filtered_Tokens'].apply(lemmatize)
        df['Pos_Tokens'] = df['Lemmatized_Tokens'].apply(pos_tagging)

        # Save the preprocessed data to a new file
        df.to_csv('dataset/preprocessed_dataset.csv', index=False)

        return df

    except FileNotFoundError:
        print(f"The file at {file_path} was not found.")
    except pd.errors.EmptyDataError:
        print("The file is empty.")
    except pd.errors.ParserError:
        print("Error parsing the file.")
    except Exception as e:
        print(f"An error occurred: {e}")


# Usage example (uncomment to run)
preprocessed_df = preprocess_data('dataset.csv')
