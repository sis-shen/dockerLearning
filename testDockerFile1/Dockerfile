FROM ubuntu:22.04 AS buildstage1
LABEL version="1.0" desc="sup test image"
ENV MYROOTDIR=/data/web/html
COPY ./nginx-1.24.0.tar.gz &{MYROOTDIR}
COPY ./index.html /data/web/html/
WORKDIR /data/src
ADD https://nginx.org/download/nginx-1.24.0.tar.gz .
RUN cd /data/src && tar -zxvf nginx-1.24.0.tar.gz
RUN apt-get update -y && apt install -y build-essential libpcre3 libpcre3-dev zlib1g-dev
RUN cd /data/src/nginx-1.24.0\
&& ./configure \
&& make && make install

COPY ./nginx.conf /usr/local/nginx/conf/ 
CMD ["/usr/local/nginx/sbin/nginx","-g","daemon off"]