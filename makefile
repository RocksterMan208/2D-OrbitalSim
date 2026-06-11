CXX := em++

CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic
CXXFLAGS += -DPLATFORM_WEB=1 -DGRAPHICS_API_OPENGL_ES2

SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build-web

TARGET := docs/play.html

RAYLIB_DIR := /home/aheal/libs/raylib
RAYLIB_SRC := $(RAYLIB_DIR)/src
RAYLIB_LIB := $(RAYLIB_SRC)/libraylib.web.a

SOURCES := $(shell find $(SRC_DIR) -name "*.cpp")
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

INCLUDES := -I$(INCLUDE_DIR) -I$(RAYLIB_SRC)

LDFLAGS := \
	-s USE_GLFW=3 \
	-s ASYNCIFY \
	-s ALLOW_MEMORY_GROWTH=1 \
	-s TOTAL_MEMORY=67108864 \
	--shell-file shell.html

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS) $(RAYLIB_LIB)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) play.html play.js play.wasm play.data

run: $(TARGET)
	emrun $(TARGET)

reset: clean all

reset-run: clean all run

.PHONY: all clean run reset reset-run