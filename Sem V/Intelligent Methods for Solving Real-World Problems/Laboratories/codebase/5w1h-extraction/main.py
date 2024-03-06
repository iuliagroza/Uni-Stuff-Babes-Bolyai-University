import logging
from who.extract_who import extract_most_relevant_person
from what.extract_what import extract_most_relevant_topic
from when.extract_when import extract_most_relevant_time
from where.extract_where import extract_most_relevant_location
from why.extract_why import extract_most_relevant_reason
from how.extract_how import extract_relevant_how_phrase

# Initialize logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')


if __name__ == "__main__":
    # Example conversation text
    """
    5W1H Extraction Possible Answers:
        Who:
            Participants: Therapist (Dr. Smith) and patient (Emily).
        What:
            Discussion about Emily's recent struggles with anxiety due to a workplace incident and stress management.
        When:
            Last meeting: Monday.
            Incident at work: Last week, specifically Wednesday morning at around 11 AM.
            Current time: 2023-04-01, 10:00 AM (session start).
        Where:
            Wellness Therapy Center (implied location of the current session).
            Office (location of the workplace incident).
        Why:
            Emily is feeling overwhelmed due to not feeling recognized at work and facing unrealistic project deadlines.
        How:
            Current coping strategy: Overworking and staying up late.
            Proposed solution: Stress management plan including relaxation techniques and setting work boundaries.
    """
    
    conversation_text = """
    Therapist: Good morning, Emily. It's great to see you again here at the Wellness Therapy Center. How have you been since our last meeting on Monday?

    Emily: Hello, Dr. Smith. Honestly, I've been struggling since last week. My anxiety spiked after the incident at work on Wednesday.

    Therapist: I'm sorry to hear that. Can you tell me more about what happened at work?

    Emily: Sure. On Wednesday morning, around 11 AM, there was a disagreement with my manager at the office. It was about the new project deadlines.

    Therapist: Understanding workplace conflicts is important. Why do you think this disagreement affected you so much?

    Emily: I guess it's because I feel my efforts are not recognized. The pressure to meet unrealistic deadlines is overwhelming.

    Therapist: That sounds quite stressful. How have you been coping with this added stress since then?

    Emily: Mostly, I've been staying up late trying to catch up on work, but it's not helping. I'm losing sleep, and my health is suffering.

    Therapist: Overworking can indeed be counterproductive. Have you tried any relaxation techniques, like meditation or deep breathing, especially during those late-night hours?

    Emily: Not really, but I'm open to suggestions. I realize I need to find better ways to manage my stress.

    Therapist: Let's work on that then. I propose we start a stress management plan, which includes relaxation techniques and setting realistic work boundaries.
    """
    session_start_str = "2023-04-01 10:00:00"

    # Extracting "Who?"
    who = extract_most_relevant_person(conversation_text)
    print("Most relevant person:", who)

    # Extracting "What?"
    what = extract_most_relevant_topic(conversation_text)
    print("Main topics of conversation:", what) 

    # Extracting "When?"
    when = extract_most_relevant_time(conversation_text, session_start_str, who, what)
    print("Most relevant temporal reference: ", when)

    # Extracting "Where?"
    where = extract_most_relevant_location(conversation_text, who, what)
    print("Most relevant location: ", where)

    # Extracting "Why?"
    why = extract_most_relevant_reason(conversation_text)
    print("Underlying reason:", why)

    # Extracting "How?"
    how = extract_relevant_how_phrase(conversation_text)  
    print("Most Relevant 'How?' Phrase:", how)

