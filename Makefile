CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -lm
STACK_SOURCES = $(wildcard ./stack/*.c)
CALCULATOR_SOURCES = $(wildcard ./calculator/*.c)
STACK_OBJECTS = $(patsubst ./stack/%.c, OBJ/stack/%.o, $(STACK_SOURCES))
CALCULATOR_OBJECTS = $(patsubst ./calculator/%.c, OBJ/calculator/%.o, $(CALCULATOR_SOURCES))
TARGET = test

all: $(TARGET)

$(TARGET): $(STACK_OBJECTS) $(CALCULATOR_OBJECTS)
	$(CC) $(STACK_OBJECTS) $(CALCULATOR_OBJECTS) -o $(TARGET) -lm

OBJ/stack/%.o: ./stack/%.c
	@mkdir -p $(@D)  # Создать директорию, если она не существует
	$(CC) $(CFLAGS) -c $< -o $@ -lm

OBJ/calculator/%.o: ./calculator/%.c
	@mkdir -p $(@D)  # Создать директорию, если она не существует
	$(CC) $(CFLAGS) -c $< -o $@ -lm

cppcheck: 
	cppcheck --enable=all --suppress=missingIncludeSystem 

clang: 
	clang-format -i $(STACK_SOURCES) $(CALCULATOR_SOURCES) ./stack/*.h ./calculator/*.h
	clang-format -n $(STACK_SOURCES) $(CALCULATOR_SOURCES) ./stack/*.h ./calculator/*.h

valgrind: test
	valgrind --tool=memcheck --leak-check=yes --log-file="valgrind.log" ./$(TARGET)

clean:
	rm -rf OBJ/ $(TARGET) valgrind.log
