CC = clang
EXE = mem_watch
BUILD_DIR = build

OJB = mem_watch.o

all: build ${EXE}

build:
	mkdir -p ${BUILD_DIR}

${BUILD_DIR}/mem_watch.c : build
	${CC} -c mem_watch.c -o ${BUILD_DIR}/mem_watch.o

mem_watch: ${BUILD_DIR}/mem_watch.c
	${CC} ${BUILD_DIR}/mem_watch.o -o mem_watch


clean:
	rm -rf ${BUILD_DIR} ${EXE}
