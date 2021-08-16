ADD_DIR=qrcode
SUB_DIR=./

INC_DIR= -I${ADD_DIR}/inc \
         -I${SUB_DIR}

SRC = ${wildcard  ${ADD_DIR}/src/*.c} \
      ${wildcard  ${SUB_DIR}/*.c}

OBJ = ${patsubst %.c, %.o, ${SRC}}

TARGET=output
CC=gcc -std=c99
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
