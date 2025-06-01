all: obj/ build/ obj/main.o build/3d obj/builder.o build/builder 

clean:
	rm -r obj/ build/ 
.PHONY: clean

obj/:
	mkdir -p obj/

build/:
	mkdir -p build/

ifndef res
res := 10
endif
ifndef debug
debug := 0
endif
obj/main.o: src/main.c
	${CC} src/main.c -c -o obj/main.o -Dres=${res} -Ddebug=${debug} 

build/3d: obj/main.o 
	gcc obj/main.o  -o build/3d -lGL -lSDL2 -lm -lSDL2_mixer 

obj/builder.o: src/builder.c
	${CC} src/builder.c -c -o obj/builder.o -Dres=${res} -Ddebug=${debug} 

build/builder: obj/builder.o 
	gcc obj/builder.o  -o build/builder -lGL -lSDL2 -lm -lSDL2_mixer 

