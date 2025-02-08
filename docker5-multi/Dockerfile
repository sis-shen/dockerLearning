FROM ubuntu:22.04 AS buildstage1

WORKDIR /src
COPY ./demo.cpp .
RUN apt update && apt install -y g++

RUN g++ demo.cpp -o demo && \
    rm -f demo.cpp && \
    apt remove -y g++ && \
    apt autoremove -y  && \
    apt clean -y

CMD ["/src/demo"]

FROM busybox
COPY --from=buildstage1 /src/demo /src/demo
# CMD ["/src/demo"]
