FROM python:3

COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY . .

# TODO: mount secret file
ENV TOKEN='secret'
ENV NEKOS_SOURCE='https://api.thecatapi.com/v1/images/search'

CMD [ "cmake", "-S", ".", "-B", "build" ]
CMD [ "cmake", "--build", "build" ]
