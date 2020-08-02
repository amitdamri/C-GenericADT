Glob: Countries.o HashTable.o KeyValuePair.o LinkedList.o Main.o
	gcc Countries.o HashTable.o KeyValuePair.o LinkedList.o Main.o -o Globe

Countries.o: Countries.c Countries.h Defs.h
	gcc -c Countries.c

HashTable.o: HashTable.c HashTable.h Defs.h KeyValuePair.h LinkedList.h
	gcc -c HashTable.c

KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c

LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c

Main.o: Main.c Countries.h Defs.h HashTable.h
	gcc -c Main.c

clean:
	rm -f *.o rm -f Globe
