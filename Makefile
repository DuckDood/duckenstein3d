all: obj/ build/ obj/main.o build/output 

clean:
	rm -r obj/ build/ 
.PHONY: clean

obj/:
	mkdir -p obj/

build/:
	mkdir -p build/

obj/main.o: src/main.c
	${CC} src/main.c -c -o obj/main.o 

build/output: obj/main.o 
	gcc obj/main.o  -o build/output -lGL -lSDL2 -lm 

