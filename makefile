List: main.o linkedList.o givenFunctions.o
	gcc -o List main.o linkedList.o givenFunctions.o

main.o: main.c header.h
	gcc -c main.c

linkedList.o: linkedList.c header.h
	gcc -c linkedList.c

givenFunctions.o: givenFunctions.c header.h
	gcc -c givenFunctions.c

 