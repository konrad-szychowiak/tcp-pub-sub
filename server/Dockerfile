FROM gcc as builder

# Set up the environment

RUN apt-get update && apt-get install --no-install-recommends cmake -y

COPY src /app/src
COPY CMakeLists.txt /app

WORKDIR /app

RUN cmake . && cmake --build .
RUN ls -la

FROM ubuntu

COPY --from=builder /app/server /usr/bin/sk2server

RUN ls -la /usr/bin

CMD ["sk2server"]
