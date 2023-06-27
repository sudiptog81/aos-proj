all:
	gcc -o main *.c
	doxygen Doxyfile

clean:
	rm -f main

docs:
	doxygen Doxyfile

run:
	./main

