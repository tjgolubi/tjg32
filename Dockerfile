FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    cmake \
    git \
    make \
    libboost-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN make

CMD ["make", "test"]

