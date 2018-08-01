filem: creating.o dirListing.o reading.o status.o writing.o main.o
	g++ -o filem creating.cpp dirListing.cpp reading.cpp status.cpp writing.cpp main.cpp
creating.o: creating.cpp a2.h
	g++ -c creating.cpp

dirListing.o: dirListing.cpp a2.h
	g++ -c dirListing.cpp
reading.o: reading.cpp a2.h
	g++ -c reading.cpp
status.o : status.cpp a2.h
	g++ -c status.cpp
writing.o: writing.cpp a2.h
	g++ -c writing.cpp
main.o: main.cpp a2.h
	g++ -c main.cpp
clean:
	rm *.o
