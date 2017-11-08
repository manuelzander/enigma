enigma: main.o plugboard.o rotor.o reflector.o enigma.o
	g++ -g main.o plugboard.o rotor.o reflector.o enigma.o -o enigma

enigma.o: enigma.cpp enigma.h plugboard.h rotor.h reflector.h errors.h helper.h
	g++ -Wall -g -c enigma.cpp

main.o: main.cpp enigma.h plugboard.h rotor.h errors.h helper.h
	g++ -Wall -g -c main.cpp

plugboard.o: plugboard.cpp plugboard.h errors.h helper.h
	g++ -Wall -g -c plugboard.cpp

rotor.o: rotor.cpp rotor.h errors.h helper.h
	g++ -Wall -g -c rotor.cpp

reflector.o: reflector.cpp reflector.h errors.h helper.h
		g++ -Wall -g -c reflector.cpp

clean:
	rm *.o enigma
