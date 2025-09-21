### BUILD ###
FROM alpine:3.21.3 AS builder

RUN set -ex && \
    apk add --no-cache \
    build-base \
    git \
    cmake \
    openssl-dev \
    zlib-dev

WORKDIR /app
COPY CMakeLists.txt CMakeLists.txt
COPY src/ src/
COPY include/ include/

RUN cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCURL_USE_OPENSSL=ON \
    -DCURL_ZLIB=ON \
    -DCURL_USE_LIBPSL=OFF
    # -DCMAKE_POSITION_INDEPENDENT_CODE=ON
    # -DBUILD_SHARED_LIBS=OFF \
    # -DCMAKE_EXE_LINKER_FLAGS="-static"

RUN cmake --build build -j$(nproc)

### --- runtime --- ###
FROM alpine:3.21.3 AS runtime

RUN set -ex && \
    apk add --no-cache \
    ca-certificates \
    openssl \
    zlib \
    gdb

WORKDIR /app
COPY --from=builder /usr/lib/*.so* /usr/lib/
COPY --from=builder /app/build/libneko.so /usr/lib/
COPY --from=builder /app/build/_deps/dpp-build/library/libdpp.so* /usr/lib/
COPY --from=builder /app/build/mettaton .
COPY secret .

CMD ["./mettaton"]
