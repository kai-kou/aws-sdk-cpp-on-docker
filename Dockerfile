FROM ubuntu:18.04

RUN apt-get update && \
    apt-get install -y git build-essential cmake clang libssl-dev

RUN apt-get update && \
    apt-get install -y libcurl4-openssl-dev libssl-dev uuid-dev zlib1g-dev libpulse-dev
RUN git clone https://github.com/aws/aws-sdk-cpp.git && \
    mkdir aws-sdk-cpp-build && \
    cd aws-sdk-cpp-build && \
    cmake -DBUILD_ONLY="s3" ../aws-sdk-cpp && \
    make && \
    make install