enigma: main.o plugboard.o rotors.o reflector.o enigma.o
	g++ -g main.o plugboard.o rotors.o reflector.o enigma.o -o enigma

enigma.o: enigma.cpp enigma.h plugboard.h rotors.h reflector.h errors.h helper.h
	g++ -Wall -g -c enigma.cpp

main.o: main.cpp enigma.h plugboard.h rotors.h errors.h helper.h
	g++ -Wall -g -c main.cpp

plugboard.o: plugboard.cpp plugboard.h errors.h helper.h
	g++ -Wall -g -c plugboard.cpp

rotors.o: rotors.cpp rotors.h errors.h helper.h
	g++ -Wall -g -c rotors.cpp

reflector.o: reflector.cpp reflector.h errors.h helper.h
		g++ -Wall -g -c reflector.cpp

clean:
	rm *.o enigma
