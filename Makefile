CC=gcc

# MISC Unix Commands to be used.
MKDIR = mkdir -p
RMRF = rm -rf

# Our Input and output sources. In this case src/ and bin/
SOURCE = $(wildcard src/*.c)
OBJ_FILES = $(addprefix obj/,$(notdir $(SOURCE:.c=.o)))

# Directories to create
OBJECTS = obj
BIN = bin
TARGET = $(BIN)/main

main: $(OBJ_FILES)
	$(MKDIR) $(BIN)
	$(CC) -o $(TARGET) $^
	$(RMRF) $(OBJECTS)

obj/%.o: src/%.c obj
	$(CC) -c -o $@ $<

obj:
	$(MKDIR) $(OBJECTS)

clean:
	$(RM) $(TARGET)
	$(RMRF) $(OBJECTS)
	$(RMRF) $(BIN)
