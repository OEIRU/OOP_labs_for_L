# Компилятор и флаги
CXX = g++
CXXFLAGS = -w -Wall -Wextra -std=c++17 -O2

# Список исходников и объектных файлов
SRC = empirical_distribution.cpp \
      huber_distribution.cpp \
      interface.cpp \
      main.cpp \
      mixture_distribution.cpp
OBJ = $(SRC:.cpp=.o)

# Заголовочные файлы
HEADERS = lib.h

# Исполняемый файл
TARGET = main

# Правило сборки
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка объектных файлов и исполняемого файла
clean:
	rm -f $(OBJ) $(TARGET)

# Удобная команда для повторной сборки
rebuild: clean all
