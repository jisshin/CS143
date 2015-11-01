.PHONY: testeq
testeq:
	gcc -c ./src/eventqueue.cpp -o ./obj/eventqueue.o
	gcc -c ./test/testeq.cpp -o ./obj/testeq.o
	gcc ./obj/*.o -o ./bin/testeq -lstdc++

.PHONY: clean
clean:
	rm -rf ./obj/*
	rm -rf ./bin/*
