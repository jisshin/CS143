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

	
OBJECTS := ./obj/event.o ./obj/eventqueue.o ./obj/flow.o ./obj/node.o ./obj/link.o
OBJECTS += ./obj/rxackevent.o ./obj/rxendevent.o ./obj/rxeventfactory.o ./obj/logger.o
OBJECTS += ./obj/rxfwdevent.o ./obj/rxrouteevent.o ./obj/txsrcevent.o ./obj/logevent.o
OBJECTS += ./obj/networkmanager.o ./obj/tcpreno.o ./obj/routeevent.o
OBJECTS += ./obj/tcptimeoutevent.o

testcase0:
	gcc -c $(CXXFLAG) ./src/eventqueue.cpp -o ./obj/eventqueue.o
	gcc -c $(CXXFLAG) ./src/event.cpp -o ./obj/event.o
	gcc -c $(CXXFLAG) ./src/flow.cpp -o ./obj/flow.o
	gcc -c $(CXXFLAG) ./src/node.cpp -o ./obj/node.o
	gcc -c $(CXXFLAG) ./src/link.cpp -o ./obj/link.o
	gcc -c $(CXXFLAG) ./src/event/rxackevent.cpp -o ./obj/rxackevent.o
	gcc -c $(CXXFLAG) ./src/event/rxendevent.cpp -o ./obj/rxendevent.o
	gcc -c $(CXXFLAG) ./src/event/rxeventfactory.cpp -o ./obj/rxeventfactory.o
	gcc -c $(CXXFLAG) ./src/event/rxfwdevent.cpp -o ./obj/rxfwdevent.o
	gcc -c $(CXXFLAG) ./src/event/rxrouteevent.cpp -o ./obj/rxrouteevent.o
	gcc -c $(CXXFLAG) ./src/event/txsrcevent.cpp -o ./obj/txsrcevent.o
	gcc -c $(CXXFLAG) ./src/networkmanager.cpp -o ./obj/networkmanager.o
	gcc -c $(CXXFLAG) ./test/testcase0.cpp -o ./obj/testcase0.o
	gcc -c $(CXXFLAG) ./src/tcpalgorithm/tcpreno.cpp -o ./obj/tcpreno.o
	gcc -c $(CXXFLAG) ./src/event/logevent.cpp -o ./obj/logevent.o
	gcc -c $(CXXFLAG) ./src/event/routeevent.cpp -o ./obj/routeevent.o
	gcc -c $(CXXFLAG) ./src/logger.cpp -o ./obj/logger.o
	gcc -c $(CXXFLAG) ./src/event/tcptimeoutevent.cpp -o ./obj/tcptimeoutevent.o

	gcc -o ./bin/testcase0 -lstdc++ ./obj/testcase0.o $(OBJECTS)   

testcase1:
	gcc -c $(CXXFLAG) ./src/eventqueue.cpp -o ./obj/eventqueue.o
	gcc -c $(CXXFLAG) ./src/event.cpp -o ./obj/event.o
	gcc -c $(CXXFLAG) ./src/flow.cpp -o ./obj/flow.o
	gcc -c $(CXXFLAG) ./src/node.cpp -o ./obj/node.o
	gcc -c $(CXXFLAG) ./src/link.cpp -o ./obj/link.o
	gcc -c $(CXXFLAG) ./src/event/rxackevent.cpp -o ./obj/rxackevent.o
	gcc -c $(CXXFLAG) ./src/event/rxendevent.cpp -o ./obj/rxendevent.o
	gcc -c $(CXXFLAG) ./src/event/rxeventfactory.cpp -o ./obj/rxeventfactory.o
	gcc -c $(CXXFLAG) ./src/event/rxfwdevent.cpp -o ./obj/rxfwdevent.o
	gcc -c $(CXXFLAG) ./src/event/rxrouteevent.cpp -o ./obj/rxrouteevent.o
	gcc -c $(CXXFLAG) ./src/event/txsrcevent.cpp -o ./obj/txsrcevent.o
	gcc -c $(CXXFLAG) ./src/networkmanager.cpp -o ./obj/networkmanager.o
	gcc -c $(CXXFLAG) ./test/testcase1.cpp -o ./obj/testcase1.o
	gcc -c $(CXXFLAG) ./src/tcpalgorithm/tcpreno.cpp -o ./obj/tcpreno.o
	gcc -c $(CXXFLAG) ./src/event/logevent.cpp -o ./obj/logevent.o
	gcc -c $(CXXFLAG) ./src/event/routeevent.cpp -o ./obj/routeevent.o
	gcc -c $(CXXFLAG) ./src/logger.cpp -o ./obj/logger.o
	gcc -c $(CXXFLAG) ./src/event/tcptimeoutevent.cpp -o ./obj/tcptimeoutevent.o

	gcc -o ./bin/testcase1 -lstdc++ ./obj/testcase1.o $(OBJECTS)   

testretrieve:
	gcc -c ./src/event/rxevent.cpp -o ./obj/rxevent.o
	gcc -c ./src/event/txevent.cpp -o ./obj/txevent.o
	gcc -c ./src/eventqueue.cpp -o ./obj/eventqueue.o
	gcc -c ./src/link.cpp -o ./obj/link.o
	gcc -c ./src/flow.cpp -o ./obj/flow.o
	gcc -c ./src/node.cpp -o ./obj/node.o
	gcc -c ./src/networkmanager.cpp -o ./obj/networkmanager.o
	gcc -c ./lib/lib_json/json_writer.cpp -o ./obj/json_writer.o
	gcc -c ./lib/lib_json/json_value.cpp -o ./obj/json_value.o
	gcc -c ./lib/lib_json/json_reader.cpp -o ./obj/json_reader.o
	gcc -c ./src/retrieve_network_info.cpp -o ./obj/retrieve_network_info.o
	gcc -c ./test/retrieve_network_info_test.cpp -o ./obj/retrieve_network_info_test.o

	gcc ./obj/*.o -o ./bin/testretrieve -lstdc++

.PHONY: clean
clean:
	rm -rf ./obj/*
	rm -rf ./bin/*
