# Определение компилятора и флагов
CXX = g++
CXXFLAGS = -Wall -Iinclude

# Определение папок
SRC_DIR = src
OBJ_DIR = obj
DATA_DIR = data
INCLUDE_DIR = include

# Определение файлов
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Имя исполняемого файла
TARGET = lab1

# Правила сборки
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка объектных файлов и исполняемого файла
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

# Правило по умолчанию
.PHONY: all clean
