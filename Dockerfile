FROM ubuntu:22.04

WORKDIR /app

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libcurl4-openssl-dev \
    libssl-dev \
    libboost-system-dev \
    zlib1g-dev \
    libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/nlohmann/json.git && \
    mkdir -p /usr/local/include/nlohmann && \
    cp json/single_include/nlohmann/json.hpp /usr/local/include/nlohmann/ && \
    rm -rf json

RUN git clone https://github.com/reo7sp/tgbot-cpp.git && \
    cd tgbot-cpp && \
    cmake . && \
    make -j$(nproc) && \
    make install && \
    cd .. && \
    rm -rf tgbot-cpp

RUN cd /usr/src/gtest && \
    cmake . && \
    make && \
    cp lib/*.a /usr/lib && \
    ln -s /usr/src/gtest/include/gtest /usr/include/gtest

COPY . .

RUN mkdir -p build && \
    cd build && \
    cmake .. && \
    make -j$(nproc)

CMD ["./build/bin/telegram_bot"]