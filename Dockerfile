# build
FROM alpine:3.21.3 AS neko-build

RUN set -ex && \
    apk add --no-cache gcc musl-dev

RUN set -ex && \
    rm -f /usr/libexec/gcc/x86_64-alpine-linux-musl/6.4.0/cc1obj && \
    rm -f /usr/libexec/gcc/x86_64-alpine-linux-musl/6.4.0/lto1 && \
    rm -f /usr/libexec/gcc/x86_64-alpine-linux-musl/6.4.0/lto-wrapper && \
    rm -f /usr/bin/x86_64-alpine-linux-musl-gcj

WORKDIR /src
COPY . .

ENV TOKEN_LOC='secret'
ENV NEKOS_SOURCE='https://api.thecatapi.com/v1/images/search'
ENV NEKO_STORE_LOC='neko-store.json'
ENV NEKOS_BATCH='20'

CMD [ "cmake", "-B", "build" ]
CMD [ "cmake", "--build", "build" ]

# runtime
FROM