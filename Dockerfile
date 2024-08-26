FROM ubuntu:22.04

COPY ./ /project

WORKDIR /project

RUN apt-get update
RUN apt-get install -y doxygen graphviz

CMD ["sh", "-c", "doxygen doxy_file"]

