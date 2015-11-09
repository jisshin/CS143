.PHONY: test
test:
	make testeq
	make testnm
	make testnl
	#make testevent

run:
	@./bin/testeq
	@./bin/testnm
	@./bin/testnl
	#./bin/testevent

testeq:
	gcc -c ./src/eventqueue.cpp -o ./obj/eventqueue.o
	gcc -c ./test/testeq.cpp -o ./obj/testeq.o

	gcc ./obj/eventqueue.o ./obj/testeq.o -o ./bin/testeq -lstdc++

testnm:
	gcc -c ./src/networkmanager.cpp -o ./obj/networkmanager.o
	gcc -c ./src/link.cpp -o ./obj/link.o
	gcc -c ./src/node.cpp -o ./obj/node.o
	gcc -c ./src/flow.cpp -o ./obj/flow.o
	gcc -c ./test/testnm.cpp -o ./obj/testnm.o

	gcc ./obj/networkmanager.o ./obj/link.o ./obj/node.o ./obj/flow.o ./obj/testnm.o -o ./bin/testnm -lstdc++ 

testnl:
	gcc -c ./src/link.cpp -o ./obj/link.o
	gcc -c ./src/node.cpp -o ./obj/node.o
	gcc -c ./test/testnl.cpp -o ./obj/testnl.o

	gcc ./obj/link.o ./obj/node.o ./obj/testnl.o -o ./bin/testnl -lstdc++ 

	
testevent:
	gcc -c $(CXXFLAG) ./src/eventqueue.cpp -o ./obj/eventqueue.o
	gcc -c $(CXXFLAG) ./src/event.cpp -o ./obj/event.o
	gcc -c $(CXXFLAG) ./src/flow.cpp -o ./obj/flow.o
	gcc -c $(CXXFLAG) ./src/node.cpp -o ./obj/node.o
	gcc -c $(CXXFLAG) ./src/event/ackevent.cpp -o ./obj/ackevent.o
	gcc -c $(CXXFLAG) ./src/event/txevent.cpp -o ./obj/txevent.o
	gcc -c $(CXXFLAG) ./src/event/rxevent.cpp -o ./obj/rxevent.o
	gcc -c $(CXXFLAG) ./src/networkmanager.cpp -o ./obj/networkmanager.o
	gcc -c $(CXXFLAG) ./test/testevent.cpp -o ./obj/testevent.o
	
	gcc ./obj/eventqueue.o ./obj/event.o ./obj/flow.o ./obj/node.o ./obj/ackevent.o ./obj/txevent.o ./obj/rxevent.o ./obj/networkmanager.o ./obj/testevent.o -o ./bin/testevent -lstdc++


.PHONY: clean
clean:
	rm -rf ./obj/*
	rm -rf ./bin/*
