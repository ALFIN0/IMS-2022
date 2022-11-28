# Makefile
# Autori: Patrik Dvorscak (xdvor15), Lada Krofingerova (xkrofi00)

CPP:=g++
CPP_FLAGS:=-std=c++11

all: main

main: main.cpp main.h
	$(CPP) $(CPP_FLAGS) main.cpp -o main

run:
	./main

pack: clean
	zip 01_xdvors15_xkrofi00.zip *.h *.cc Makefile *.pdf

clean:
	rm -f *.o ./main *.zip

unpack: 
	unzip 01_xblask02_xcerny63.zip
