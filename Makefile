CC = gcc
CFLAGS = -Wall -g

BIN_DIR = bin
OBJ_DIR = build
SRC_DIR = src
INCLUDE_DIR = include

TARGET = $(BIN_DIR)/envsync
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -I$(INCLUDE_DIR) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) $(OBJECTS)
