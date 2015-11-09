.PHONY: test

CXXFLAG=-g -std=c++11

test:
	make testeq
	make testnm
	make testnl
	make testcase0

run:
	@./bin/testeq
	@./bin/testnm
	@./bin/testnl
	@./bin/testcase0

testeq:
	gcc -c $(CXXFLAG) ./src/eventqueue.cpp -o ./obj/eventqueue.o
	gcc -c $(CXXFLAG) ./test/testeq.cpp -o ./obj/testeq.o

	gcc ./obj/eventqueue.o ./obj/testeq.o -o ./bin/testeq -lstdc++

testnm:
	gcc -c $(CXXFLAG) ./src/networkmanager.cpp -o ./obj/networkmanager.o
	gcc -c $(CXXFLAG) ./src/link.cpp -o ./obj/link.o
	gcc -c $(CXXFLAG) ./src/node.cpp -o ./obj/node.o
	gcc -c $(CXXFLAG) ./src/flow.cpp -o ./obj/flow.o
	gcc -c $(CXXFLAG) ./test/testnm.cpp -o ./obj/testnm.o

	gcc ./obj/networkmanager.o ./obj/link.o ./obj/node.o ./obj/flow.o ./obj/testnm.o -o ./bin/testnm -lstdc++ 

testnl:
	gcc -c $(CXXFLAG) ./src/link.cpp -o ./obj/link.o
	gcc -c $(CXXFLAG) ./src/node.cpp -o ./obj/node.o
	gcc -c $(CXXFLAG) ./test/testnl.cpp -o ./obj/testnl.o

	gcc ./obj/link.o ./obj/node.o ./obj/testnl.o -o ./bin/testnl -lstdc++ 

	
testcase0:
	gcc -c $(CXXFLAG) ./src/eventqueue.cpp -o ./obj/eventqueue.o
	gcc -c $(CXXFLAG) ./src/event.cpp -o ./obj/event.o
	gcc -c $(CXXFLAG) ./src/flow.cpp -o ./obj/flow.o
	gcc -c $(CXXFLAG) ./src/node.cpp -o ./obj/node.o
	gcc -c $(CXXFLAG) ./src/link.cpp -o ./obj/link.o	
	gcc -c $(CXXFLAG) ./src/event/txevent.cpp -o ./obj/txevent.o
	gcc -c $(CXXFLAG) ./src/event/rxevent.cpp -o ./obj/rxevent.o
	gcc -c $(CXXFLAG) ./src/networkmanager.cpp -o ./obj/networkmanager.o
	gcc -c $(CXXFLAG) ./test/testcase0.cpp -o ./obj/testcase0.o
	
	gcc ./obj/eventqueue.o ./obj/link.o ./obj/event.o ./obj/flow.o ./obj/node.o ./obj/txevent.o ./obj/rxevent.o ./obj/networkmanager.o ./obj/testcase0.o -o ./bin/testcase0 -lstdc++


.PHONY: clean
clean:
	rm -rf ./obj/*
	rm -rf ./bin/*
