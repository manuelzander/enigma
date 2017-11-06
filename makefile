enigma: main.o plugboard.o
	g++ -g main.o plugboard.o -o enigma

main.o: main.cpp plugboard.h errors.h helper.h
	g++ -Wall -g -c main.cpp

plugboard.o: plugboard.cpp plugboard.h helper.h
	g++ -Wall -g -c plugboard.cpp

clean:
	rm *.o enigma
