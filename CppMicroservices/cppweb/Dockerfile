FROM ubuntu:22.04 AS buildstage
WORKDIR /src
COPY ./main.cpp .
RUN apt update && apt install -y g++

RUN g++ main.cpp -o cppweb -lpthread -std=c++11 && \
    rm -f demo.cpp && \
    apt remove -y g++ && \
    apt autoremove -y  && \
    apt clean -y

CMD ["/src/cppweb"]

FROM ubuntu:22.04
COPY --from=buildstage /src/cppweb /
CMD ["/cppweb"]