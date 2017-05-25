FROM i386/ubuntu:12.04 

RUN apt-get update && \
    apt-get install -y cmake libprotobuf-dev protobuf-compiler libjson-spirit-dev build-essential && \
    apt-get clean

ADD demoinfogo-linux/build-jvm-bower /tmp/jdk8-oracle-build
ADD https://raw.github.com/technomancy/leiningen/stable/bin/lein .
RUN /bin/sh /tmp/jdk8-oracle-build
ENV LEIN_ROOT 1

ADD project.clj /opt/headshotbox/project.clj
WORKDIR /opt/headshotbox
RUN lein deps
ADD . /opt/headshotbox

WORKDIR /opt/headshotbox/demoinfogo-linux/
RUN mkdir builds && cd builds && cmake .. -DRPATH=ON -DCMAKE_BUILD_TYPE=Release && make && \
mkdir libs && cp /usr/lib/i386-linux-gnu/libstdc++.so.6 /usr/lib/libprotobuf.so.7 /lib/i386-linux-gnu/libz.so.1 /lib/i386-linux-gnu/libgcc_s.so.1 libs 

WORKDIR /opt/headshotbox
RUN bower install --allow-root
EXPOSE 4000
CMD ["lein", "run"]
