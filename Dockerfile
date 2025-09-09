### BUILD ###
FROM debian:12.12 AS builder

# RUN set -ex && \
#     apk add --no-cache \
#     build-base \
#     git \
#     cmake \
#     zlib-dev \
#     curl-dev \
#     openssl-dev \
#     libidn2-dev

# ENV CFLAGS="-static" \
#     CXXFLAGS="-static" \
#     LDFLAGS="-static"

RUN apt install cmake=4.1.1

WORKDIR /app
COPY . .

RUN cmake -S . -B build

RUN cmake --build build --target mettaton -j$(nproc)

### RUN ###
FROM alpine:3.21.3 AS runtime

WORKDIR /var
COPY --from=builder /app/build/mettaton mettaton
COPY secret .

ENV TOKEN_LOC='secret'
ENV NEKOS_SOURCE='https://api.thecatapi.com/v1/images/search'
ENV NEKO_STORE_LOC='neko-store.json'
ENV NEKOS_BATCH='20'

ENTRYPOINT ["/var/mettaton"]