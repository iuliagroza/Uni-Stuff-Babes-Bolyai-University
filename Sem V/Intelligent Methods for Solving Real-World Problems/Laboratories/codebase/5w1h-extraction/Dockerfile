FROM python:3.9

WORKDIR /app

ENV HTTP_PORT 8080
ENV HOST 0.0.0.0

COPY . /app

RUN pip install --no-cache-dir -r requirements.txt

RUN python -m nltk.downloader vader_lexicon

EXPOSE 8080

CMD ["python", "app.py"]