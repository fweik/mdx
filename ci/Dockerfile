FROM ubuntu:focal

RUN apt-get update && apt-get install --no-install-recommends -y g++ clang clang-tidy cmake libboost-dev libboost-test-dev make && apt-get clean && rm -rf /var/lib/apt/lists/*
