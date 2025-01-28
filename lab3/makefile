# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# Директории
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

# Исходные файлы
SRC_FILES = $(SRC_DIR)/Empirical.cpp $(SRC_DIR)/Interface.cpp $(SRC_DIR)/Main.cpp $(SRC_DIR)/Mixture.cpp $(SRC_DIR)/Primary.cpp $(SRC_DIR)/Tests.cpp

# Объектные файлы
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Исполняемые файлы
EXEC = lab3
TEST_EXEC = lab3_tests

# Правила
all: $(EXEC) $(TEST_EXEC)

$(EXEC): $(OBJ_DIR)/Empirical.o $(OBJ_DIR)/Interface.o $(OBJ_DIR)/Main.o $(OBJ_DIR)/Mixture.o $(OBJ_DIR)/Primary.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_EXEC): $(OBJ_DIR)/Empirical.o $(OBJ_DIR)/Interface.o $(OBJ_DIR)/Mixture.o $(OBJ_DIR)/Primary.o $(OBJ_DIR)/Tests.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(EXEC) $(TEST_EXEC)

# Запуск тестов
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Запуск основного приложения
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean test run