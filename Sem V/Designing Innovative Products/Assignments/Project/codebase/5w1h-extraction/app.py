from flask import Flask, request, jsonify
from who.extract_who import extract_most_relevant_person
from what.extract_what import extract_most_relevant_topic
from when.extract_when import extract_most_relevant_time
from where.extract_where import extract_most_relevant_location
from why.extract_why import extract_most_relevant_reason
from how.extract_how import extract_relevant_how_phrase

app = Flask(__name__)

@app.route('/')
def home():
    return "5W1H Extraction API"

@app.route('/extract/5w1h', methods=['POST'])
def extract_5w1h():
    if not request.json or 'text' not in request.json or 'timestamp' not in request.json:
        return jsonify({'error': 'No text or timestamp provided'}), 400
    
    text = request.json['text']
    timestamp = request.json['timestamp']
    who = extract_most_relevant_person(text)
    what = extract_most_relevant_topic(text)

    results = {
        "who": who,
        "what": what,
        "when": extract_most_relevant_time(text, timestamp, who, what),
        "where": extract_most_relevant_location(text, who, what),
        "why": extract_most_relevant_reason(text),
        "how": extract_relevant_how_phrase(text)
    }
    return jsonify(results)


if __name__ == '__main__':
    import os
    port = int(os.environ.get('PORT', 8080))
    app.run(debug=False, host='0.0.0.0', port=port)
