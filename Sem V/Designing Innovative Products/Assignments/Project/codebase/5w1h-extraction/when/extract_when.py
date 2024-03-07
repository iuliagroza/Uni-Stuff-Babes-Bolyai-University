import spacy
import re
from datetime import datetime, timedelta
from collections import Counter
from nltk.sentiment import SentimentIntensityAnalyzer

# Load the spaCy model
nlp = spacy.load("en_core_web_lg")

def extract_absolute_times(text):
    """ Extracts absolute time and date references using spaCy NER. """
    doc = nlp(text)
    return [ent.text for ent in doc.ents if ent.label_ in ['TIME', 'DATE']]

def get_weekday_offset(current_date, target_weekday, is_next_week):
    """
    Calculate the date for the next or last occurrence of a specific weekday.

    Args:
    current_date (datetime): The current session date.
    target_weekday (int): The target weekday (0=Monday, 6=Sunday).
    is_next_week (bool): True for next week's weekday, False for last week's.

    Returns:
    datetime: The calculated date.
    """
    current_weekday = current_date.weekday()
    days_until_target = (target_weekday - current_weekday + 7) % 7
    if days_until_target == 0:  # Target is today, adjust to next/last week
        days_until_target = 7 if is_next_week else -7
    elif is_next_week and days_until_target < 7:
        days_until_target += 7  # Ensure it's the next week
    elif not is_next_week and days_until_target > 0:
        days_until_target -= 7  # Ensure it's the previous week
    return current_date + timedelta(days=days_until_target)

def get_this_weekday(current_date, target_weekday):
    """
    Calculate the date for 'this' occurrence of a specific weekday.

    Args:
    current_date (datetime): The current session date.
    target_weekday (int): The target weekday (0=Monday, 6=Sunday).

    Returns:
    datetime: The calculated date for 'this' weekday.
    """
    current_weekday = current_date.weekday()
    if current_weekday <= target_weekday:
        # This week's weekday if the session day is before or on the target weekday
        days_diff = target_weekday - current_weekday
    else:
        # Previous week's weekday if the session day is past the target weekday
        days_diff = target_weekday - current_weekday - 7
    return current_date + timedelta(days=days_diff)

def interpret_relative_times(text, session_start):
    """
    Extracts and interprets relative time references.
    
    Args:
    text (str): The text of the therapy conversation.
    session_start (datetime): The start time of the current therapy session.
    
    Returns:
    list: A list of interpreted relative time references.
    """
    weekdays = {'monday': 0, 'tuesday': 1, 'wednesday': 2, 'thursday': 3, 'friday': 4, 'saturday': 5, 'sunday': 6}
   
    # Interpret references to days of the week
    for day, day_index in weekdays.items():
        if re.search(fr'last {day}', text, re.IGNORECASE):
            date = get_weekday_offset(session_start, day_index, False)
            relative_times.append(date.strftime('%Y-%m-%d'))
        elif re.search(fr'this {day}', text, re.IGNORECASE):
            date = get_this_weekday(session_start, day_index)
            relative_times.append(date.strftime('%Y-%m-%d'))
        elif re.search(fr'next {day}', text, re.IGNORECASE):
            date = get_weekday_offset(session_start, day_index, True)
            relative_times.append(date.strftime('%Y-%m-%d'))
    
    # Define relative time patterns and their interpretations
    patterns = {
        'the day before yesterday': session_start - timedelta(days=2),
        'yesterday': session_start - timedelta(days=1),
        'today': session_start,
        'tomorrow': session_start + timedelta(days=1),
        'the day after tomorrow': session_start + timedelta(days=2),
        'last week': session_start - timedelta(weeks=1),
        'next week': session_start + timedelta(weeks=1),
        'last month': session_start - timedelta(days=30),
        'next month': session_start + timedelta(days=30),
        'last year': session_start - timedelta(days=365),
        'next year': session_start + timedelta(days=365),
    }

    # Patterns for hours (extend as needed)
    hour_patterns = {
        # 12-hour format with 'AM' or 'PM'
        r'at (\d{1,2} (?:AM|PM))': '%I %p',
        r'around (\d{1,2} (?:AM|PM))': '%I %p',
        r'by (\d{1,2} (?:AM|PM))': '%I %p',

        # 24-hour format
        r'at ((?:\d{1,2}):(?:\d{2}))': '%H:%M',
        r'around ((?:\d{1,2}):(?:\d{2}))': '%H:%M',
        r'by ((?:\d{1,2}):(?:\d{2}))': '%H:%M',
    }

    for pattern, format_str in hour_patterns.items():
        match = re.search(pattern, text, re.IGNORECASE)
        if match:
            hour_str = ' '.join(match.groups())
            hour_time = datetime.strptime(hour_str, format_str).time()
            full_datetime = datetime.combine(session_start.date(), hour_time)
            patterns[pattern] = full_datetime
    
    # Add patterns for "<X> days/weeks/months/years ago"
    time_units = {'days': 'days', 'weeks': 'weeks', 'months': 'days', 'years': 'days'}
    unit_durations = {'days': 1, 'weeks': 7, 'months': 30, 'years': 365}

    for unit in time_units.keys():
        match = re.search(rf'(\d+)\s+{unit}\s+ago', text)
        if match:
            num_units = int(match.group(1))
            duration = timedelta(**{time_units[unit]: num_units * unit_durations[unit]})
            patterns[match.group(0)] = session_start - duration

    # Add patterns for "in <X> days/weeks/months/years"
    for unit in time_units.keys():
        match = re.search(rf'in\s+(\d+)\s+{unit}', text)
        if match:
            num_units = int(match.group(1))
            duration = timedelta(**{time_units[unit]: num_units * unit_durations[unit]})
            patterns[match.group(0)] = session_start + duration

    relative_times = []
    for pattern, interpretation in patterns.items():
        if re.search(pattern, text, re.IGNORECASE):
            relative_times.append(interpretation.strftime('%Y-%m-%d'))

    return relative_times

def analyze_dependency(sentence, time_ref):
    """
    Analyzes the dependency relationship of a time reference in a sentence.

    Args:
    sentence (spacy.tokens.span.Span): A sentence containing the time reference.
    time_ref (str): The time reference to analyze.

    Returns:
    float: A score indicating the grammatical importance of the time reference.
    """
    # Parse the sentence
    doc = nlp(sentence.text)

    # Initialize importance score
    importance_score = 0

    for token in doc:
        # Check if the token is part of the time reference
        if time_ref in token.text:
            # Increase score based on grammatical role
            if token.dep_ in ['ROOT', 'nsubj', 'dobj', 'attr', 'advcl']:
                importance_score += 2  # Higher score for central grammatical roles
            elif token.dep_ in ['prep', 'pobj', 'advmod']:
                importance_score += 1  # Lower score for peripheral roles

    return importance_score

def analyze_topic_association(sentence, time_ref, who, what):
    """
    Analyzes how closely a time reference is associated with key topics in a sentence.

    Args:
    sentence (spacy.tokens.span.Span): A sentence containing the time reference.
    time_ref (str): The time reference to analyze.

    Returns:
    float: A score indicating the association of the time reference with key topics.
    """
    # Parse the sentence
    doc = nlp(sentence.text)

    # The extracted "Who?" and "What?" tokens. This ensures the temporal
    # references are relative and relevant to our extraction and all
    # questions are co-dependent.
    KEY_TOPICS = [who, what]

    # Count occurrences of key topics in the sentence
    topic_counter = Counter([token.lemma_ for token in doc if token.lemma_ in KEY_TOPICS])

    # Determine association score
    association_score = 0
    if topic_counter:
        # Increase score if the sentence with the time reference contains key topics
        association_score += sum(topic_counter.values())

    # Optional: Adjust the score based on proximity to the time reference
    for token in doc:
        if token.text == time_ref and any(topic in [child.text for child in token.children] for topic in KEY_TOPICS):
            association_score += 1  # Increase score for direct association

    return association_score

def analyze_context(text, time_references, who, what):
    doc = nlp(text)
    sia = SentimentIntensityAnalyzer()
    context_scores = {}

    # Convert sentences generator to a list
    sentences = list(doc.sents)

    for time_ref in time_references:
        context_scores[time_ref] = 0
        for sent in doc.sents:
            if time_ref in sent.text:
                # Sentiment Analysis
                sentiment_score = sia.polarity_scores(sent.text)['compound']
                context_scores[time_ref] += sentiment_score
                
                # Dependency Parsing and Topic Association (hypothetical functions)
                dep_score = analyze_dependency(sent, time_ref)
                topic_score = analyze_topic_association(sent, time_ref, who, what)
                
                context_scores[time_ref] += dep_score + topic_score

    # Normalize scores
    for time_ref in context_scores:
        if sentences:  # Check to avoid division by zero
            context_scores[time_ref] /= len(sentences)

    return context_scores

def extract_most_relevant_time(text, session_start_str, who, what):
    """
    Extracts the most relevant time reference from the therapy conversation.
    
    Args:
    text (str): The text of the therapy conversation.
    session_start_str (str): The start time of the session as a string.
    
    Returns:
    str: The most relevant time reference.
    """
    session_start = datetime.strptime(session_start_str, '%Y-%m-%d %H:%M:%S')

    # Extract absolute and relative times
    absolute_times = extract_absolute_times(text)
    relative_times = interpret_relative_times(text, session_start)

    # Combine and find unique time references
    all_times = list(set(absolute_times + relative_times))

    if not all_times:  # Check if all_times is empty
        return 'Since last session'  # or a default value, depending on your application's needs

    # Analyze the context of each time reference
    context_scores = analyze_context(text, all_times, who, what)

    # Count the frequency of each time reference
    frequency = Counter(absolute_times + relative_times)

    # Determine the most relevant time reference
    # Combining frequency and context importance
    most_relevant_time = max(all_times, key=lambda x: (frequency[x], context_scores[x]))

    return most_relevant_time
