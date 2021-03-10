CUR_DIR=mutis/main文件所处的目录

ADD_DIR=${CUR_DIR}/multis
SUB_DIR=${CUR_DIR}/main

INC_DIR= -I${ADD_DIR} \
         -I${SUB_DIR}

SRC = ${wildcard  ${ADD_DIR}/*.c} \
      ${wildcard  ${SUB_DIR}/*.c}

OBJ = ${patsubst %.c, %.o, ${SRC}}

TARGET=output
CC=gcc
CCFLAGS=-g -Wall ${INC_DIR}

${TARGET}: ${OBJ}
	${CC} ${notdir ${OBJ}} -o $@
	echo "Compile done."
${OBJ}:${SRC}
	$(CC) ${CCFLAGS} -c $? 

clean:
	rm -f ${OBJ}
	rm -f *.o
	rm -f *~
	rm -f ${TARGET}
	echo "Clean done."
