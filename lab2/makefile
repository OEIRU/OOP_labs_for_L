# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.

# Исходные файлы
SRC_DIR = .
SRC_FILES = $(SRC_DIR)/Interface.cpp $(SRC_DIR)/Primary.cpp $(SRC_DIR)/Main.cpp $(SRC_DIR)/Tests.cpp

# Объектные файлы
OBJ_DIR = obj
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Исполняемые файлы
EXEC = lab2
TEST_EXEC = lab2_tests

# Правила
all: $(EXEC) $(TEST_EXEC)

$(EXEC): $(OBJ_DIR)/Interface.o $(OBJ_DIR)/Primary.o $(OBJ_DIR)/Main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_EXEC): $(OBJ_DIR)/Interface.o $(OBJ_DIR)/Primary.o $(OBJ_DIR)/Tests.o
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