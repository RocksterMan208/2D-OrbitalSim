CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
TARGET := play

SOURCES := $(shell find $(SRC_DIR) -name "*.cpp")
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# SDL2 via pkg-config (correct usage)
SDL2_CFLAGS := $(shell pkg-config --cflags sdl2)
SDL2_LIBS := $(shell pkg-config --libs sdl2)

INCLUDES := -I$(INCLUDE_DIR) $(SDL2_CFLAGS)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(OBJECTS) -o $@ $(SDL2_LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

reset: clean all run

.PHONY: all clean run reset