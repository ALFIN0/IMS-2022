# Makefile
# Autori: Patrik Dvorscak (xdvor15), Lada Krofingerova (xkrofi00)

CPP:=g++
CPP_FLAGS:=-std=c++11 -lGLU -lGL -lglut

all: main

main: main.cpp main.h cell.cpp cell.h grid.cpp grid.h
	$(CPP) $(CPP_FLAGS) main.cpp cell.cpp grid.cpp -o main

run: main
	./main

pack: clean
	zip 11_xdvors15_xkrofi00.zip *.h *.cpp Makefile *.pdf

clean:
	rm -f *.o ./main *.zip

unpack: 
	unzip 11_xdvors15_xkrofi00.zip
