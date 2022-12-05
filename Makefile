# Makefile
# Autori: Patrik Dvorscak (xdvor15), Lada Krofingerova (xkrofi00)

CPP:=g++
CPP_FLAGS:=-std=c++11
OPENGL_FLAGS= -lGLU -lGL -lglut

all: main

main: main.cpp main.h cell.cpp cell.h grid.cpp grid.h
	$(CPP) $(CPP_FLAGS) main.cpp cell.cpp grid.cpp -o main $(OPENGL_FLAGS)

run: main
	test -d stats || mkdir stats
	./main -t 50 -f stats/file.txt -x 100 -y 100

run-small-forestation: main
	test -d stats || mkdir stats
	./main -t 50 -f stats/file.txt -x 100 -y 100 -p 30

run-stats: main
	test -d stats || mkdir stats
	test -f stats/stats.csv || echo "weeks;colonieslow;coloniesmed;colonieshigh;treeshea;treesatt;treedec;fields;temp;begincolonies" >> stats/stats.csv
	./main -t 50 -f stats/file.txt -x 400 -y 400 -T 24 -S stats/stats.csv

run-complex-stats: main script.sh
	sh script.sh

pack: clean
	zip 11_xdvors15_xkrofi00.zip *.h *.cpp Makefile *.pdf *.sh simulation-files/*

clean:
	rm -rf *.o ./main *.zip stats

unpack: 
	unzip 11_xdvors15_xkrofi00.zip
