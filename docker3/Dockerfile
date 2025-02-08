FROM ubuntu:22.04
RUN apt-get update -y && apt install -y iputils-ping
ENTRYPOINT [ "ping","-c","3" ]
CMD ["localhost"]