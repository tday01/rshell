all: ./bin/rshell

./bin/rshell: ./src/main.cpp ./src/command.cpp ./src/command.h
	mkdir -p ./bin/
	g++ -o ./bin/rshell ./src/main.cpp ./src/command.cpp

run_tests:
	cd ./tests/ && ./run_tests.sh

clean:
	rm -rf ./bin/
	rm -rf ./tests/actual
