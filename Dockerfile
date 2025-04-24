FROM python:3

COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY . .

ENV TOKEN_LOC='secret'
ENV NEKOS_SOURCE='https://api.thecatapi.com/v1/images/search'
ENV NEKO_STORE_LOC='neko-store'
ENV NEKOS_BATCH='20'

CMD [ "python", "main.py" ]
