run_test:
	./bin/testeq

testeq:
	gcc -c $(CXXFLAG) ./src/eventqueue.cpp -o ./obj/eventqueue.o
	gcc -c $(CXXFLAG) ./test/testeq.cpp -o ./obj/testeq.o

	gcc ./obj/*.o -o ./bin/testeq -lstdc++
	
CXXFLAG = 
all:
	gcc -c $(CXXFLAG) ./src/eventqueue.cpp -o ./obj/eventqueue.o
	gcc -c $(CXXFLAG) ./src/event.cpp -o ./obj/event.o
	gcc -c $(CXXFLAG) ./src/flow.cpp -o ./obj/flow.o
	gcc -c $(CXXFLAG) ./src/node.cpp -o ./obj/node.o
	gcc -c $(CXXFLAG) ./src/event/ackevent.cpp -o ./obj/ackevent.o
	gcc -c $(CXXFLAG) ./src/event/txevent.cpp -o ./obj/txevent.o
	gcc -c $(CXXFLAG) ./src/event/rxevent.cpp -o ./obj/rxevent.o
	gcc -c $(CXXFLAG) ./src/networkmanager.cpp -o ./obj/networkmanager.o
	gcc -c $(CXXFLAG) ./test/testevent.cpp -o ./obj/testeq.o
	
	gcc ./obj/*.o -o ./bin/testevent -lstdc++

.PHONY: clean
clean:
	rm -rf ./obj/*
	rm -rf ./bin/*
