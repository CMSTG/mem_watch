CC = clang
EXE = mem_watch
BUILD_DIR = build

OJB = mem_watch.o

INSTALL_DIR = ~/.local/bin/

GIT_COMMIT = $(shell git log -n 1 main --pretty="%h")

all: build ${EXE}

build:
	mkdir -p ${BUILD_DIR}

${BUILD_DIR}/mem_watch.c : build
	${CC} -c mem_watch.c -o ${BUILD_DIR}/mem_watch.o -DGIT_COMMIT='"${GIT_COMMIT}"'

mem_watch: ${BUILD_DIR}/mem_watch.c
	${CC} ${BUILD_DIR}/mem_watch.o -o mem_watch

install:
	cp ${EXE} `realpath ${INSTALL_DIR}`


clean:
	rm -rf ${BUILD_DIR} ${EXE}
