FLAGS := -Wall -Wextra -fsanitize=address,undefined
BIN := ./bin
INCLUDE := ./include
SRC := ./src

all: bin $(BIN)/main

bin:
	@if [ ! -d $(BIN) ]; then mkdir $(BIN); fi

$(BIN)/constant.o: $(INCLUDE)/constant.hpp $(SRC)/constant.cpp
	$(CXX) -c $(SRC)/constant.cpp -o $(BIN)/constant.o $(FLAGS) -I$(INCLUDE)

$(BIN)/variable.o: $(INCLUDE)/variable.hpp $(SRC)/variable.cpp $(INCLUDE)/functions.hpp $(SRC)/functions.cpp
	$(CXX) -c $(SRC)/variable.cpp -o $(BIN)/variable.o $(FLAGS) -I$(INCLUDE)

$(BIN)/unary_operation.o: $(INCLUDE)/unary_operation.hpp $(SRC)/unary_operation.cpp $(INCLUDE)/functions.hpp $(SRC)/functions.cpp
	$(CXX) -c $(SRC)/unary_operation.cpp -o $(BIN)/unary_operation.o $(FLAGS) -I$(INCLUDE)

$(BIN)/binary_operation.o: $(INCLUDE)/binary_operation.hpp $(SRC)/binary_operation.cpp $(INCLUDE)/functions.hpp $(SRC)/functions.cpp
	$(CXX) -c $(SRC)/binary_operation.cpp -o $(BIN)/binary_operation.o $(FLAGS) -I$(INCLUDE)

$(BIN)/functions.o: $(INCLUDE)/functions.hpp $(SRC)/functions.cpp
	$(CXX) -c $(SRC)/functions.cpp -o $(BIN)/functions.o $(FLAGS) -I$(INCLUDE)

$(BIN)/main: $(BIN)/constant.o $(BIN)/variable.o $(BIN)/unary_operation.o $(BIN)/binary_operation.o $(BIN)/functions.o main.cpp
	$(CXX) main.cpp $(BIN)/constant.o $(BIN)/variable.o $(BIN)/unary_operation.o $(BIN)/binary_operation.o $(BIN)/functions.o -o $(BIN)/main $(FLAGS) -I$(INCLUDE)

clean:
	@if [ -d $(BIN) ]; then rm -rf $(BIN); fi