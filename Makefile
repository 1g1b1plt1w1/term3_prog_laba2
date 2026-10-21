CXX      = g++
CXXFLAGS = -std=c++17 -Istr -Itasks -Wall -Wextra

TARGET = main

SRC = main.cpp \
      str/array.cpp \
      str/linked_list.cpp \
      str/one_linked_list.cpp \
      str/stack.cpp \
      str/queue.cpp \
      str/tree.cpp \
      str/open_hash.cpp \
      str/Set.cpp \
      str/lru.cpp \
      tasks/task1.cpp \
      tasks/task4.cpp \
      tasks/task3.cpp \
      tasks/task5.cpp \
      tasks/task7.cpp

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# единое правило компиляции для любых .cpp
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

rebuild: clean all

run: all
	./$(TARGET)

.PHONY: all clean rebuild run
