gcc -c main.c -o main.o
gcc -c sqlite3.c -o sqlite3.o
gcc main.o sqlite3.o -o run -lpthread -ldl
