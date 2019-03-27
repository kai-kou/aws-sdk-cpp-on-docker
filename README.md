# aws-sdk-cpp-on-docker

DockerとMinioでAWS SDK for C++の開発環境を構築する  

## Usage

```sh
> git clone https://github.com/kai-kou/aws-sdk-cpp-on-docker.git
> cd aws-sdk-cpp-on-docker
> docker-compose up -d minio
> docker-compose run dev bash
# cd /cpp-dev/build
# cmake ..
# cmake --build .
# ./main
```