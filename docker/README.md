# Dockerfile

Dockerに移植しました.

BUILD:
    
    $ cd Container_Club/docker/
    $ docker build -t tomoyk/snakegame:1.3 .

UPLOAD_DOCKERHUB

    $ docker login
    $ docker push tomoyk/snakegame:1.3

RUN:

    $ docker pull tomoyk/snakegame
    $ docker run -it --rm tomoyk/snakegame:1.3

