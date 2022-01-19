FROM gcc:8.1.0 as build

WORKDIR /ffutil

RUN apt-get -y  update && apt-get -y upgrade && \
    apt-get -y install libavformat-dev libavcodec-dev libavutil-dev libswscale-dev libswresample-dev \
    cmake

ADD . /ffutil/project

WORKDIR /ffutil/project/build

RUN cmake ../ && \
    cmake --build .

FROM ubuntu:18.04

WORKDIR /ffutil

COPY --from=build /ffutil/project/build/ffutil .

RUN apt-get update && apt-get upgrade && \
    apt-get -y install ffmpeg && \
    groupadd ffgroup && useradd -u 1000 -g ffgroup ffuser && \
    chown -R ffuser:ffgroup /ffutil
   
USER ffuser

#ENTRYPOINT ["./ffutil"]
