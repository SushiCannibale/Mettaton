# building lib
FROM alpine/curl:8.12.1 AS nekolib-build
RUN apk add cmake=4.0.1

WORKDIR /src
COPY . .

ENV TOKEN_LOC='secret'
ENV NEKOS_SOURCE='https://api.thecatapi.com/v1/images/search'
ENV NEKO_STORE_LOC='neko-store.json'
ENV NEKOS_BATCH='20'

CMD [ "cmake", "-B", "build" ]
CMD [ "cmake", "--build", "build" ]