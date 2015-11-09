.PHONY: test
test:
	make testeq
	make testnm
	make testevent

run:
	@./bin/testeq
	@./bin/testnm
	@./bin/testevent

testeq:
	gcc -c ./src/eventqueue.cpp -o ./obj/eventqueue.o
	gcc -c ./test/testeq.cpp -o ./obj/testeq.o

	gcc ./obj/*.o -o ./bin/testeq -lstdc++

testnm:
	gcc -c ./src/networkmanager.cpp -o ./obj/networkmanager.o
	gcc -c ./test/testnm.cpp -o ./obj/testeq.o

	gcc ./obj/*.o -o ./bin/testnm -lstdc++

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

	gcc ./obj/*.o -o ./bin/testevent -lstdc++

testretrieve:
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
