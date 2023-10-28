CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Wno-unused-parameter -Werror=init-self
LIBS = -lm -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer -lSDL2_ttf

SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin

SRC_FILES = $(wildcard $(SRC_DIR)/**/*.cpp) $(SRC_DIR)/Main.cpp
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEP_FILES = $(OBJ_FILES:.o=.d)

DEBUG ?= 0
ifeq ($(DEBUG), 1)
    CFLAGS += -DDEBUG -g3 -ggdb -O0
else
    CFLAGS += -DNDEBUG -O3 -mtune=native
endif

PROGRAMS = penguin

.PHONY: all
all: setup $(PROGRAMS)

.PHONY: setup
setup:
	mkdir -p $(BIN_DIR) $(sort $(dir $(OBJ_FILES)))

penguin: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $(BIN_DIR)/$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(LIBS) -c -MMD -MP $< -o $@

-include $(DEP_FILES)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/* $(addprefix $(BIN_DIR)/,$(PROGRAMS))