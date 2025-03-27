FROM ubuntu:22.04 AS buildstage 

RUN apt-get update -y
RUN apt install -y gcc-9 g++-9 g++-9 binutils make 
ADD redis7.tar.gz /
ADD redis.conf /redis/
WORKDIR /redis-7.4.2
RUN CC=gcc-9 CXX=g++-9 make
RUN  mv /redis-7.4.2/src/redis-server /redis/ && mv /redis-7.4.2/src/redis-cli /redis/ 
ENTRYPOINT ["/redis/redis-server", "/redis/redis.conf"] 

FROM ubuntu:22.04 
RUN mkdir -p /data/redis && mkdir -p /redis 
COPY --from=buildstage /redis /redis 
EXPOSE 6379 
ENTRYPOINT ["/redis/redis-server", "/redis/redis.conf"]