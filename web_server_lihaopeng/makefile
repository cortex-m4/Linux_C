a.out:sqlite3.o main.o sousuo.o
	gcc $^ -o $@ -lpthread -ldl
sqlite3.o:sqlite3.c
	gcc -c sqlite3.c -o sqlite3.o
main.o:project_main.c
	gcc -c project_main.c -o main.o
sousuo.o:sousuo.c
	gcc -c sousuo.c -o sousuo.o
.PHONY:
clean: 
	rm a.out
