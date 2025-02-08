FROM ubuntu:22.04

WORKDIR /src
COPY ./demo.cpp .
RUN apt update && apt install -y g++

RUN g++ demo.cpp -o demo && \
    rm -f demo.cpp && \
    apt remove -y g++ && \
    apt autoremove -y  && \
    apt clean -y

CMD ["/src/demo"]