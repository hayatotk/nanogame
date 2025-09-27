CXX := g++
CXXFLAGS := -std=c++17 -Wall -O2 -Isrc -Isrc/core -Isrc/platform/SDL_uni
LDFLAGS := -lSDL2 -lSDL2_ttf

SRC_DIR := src
CORE_DIR := $(SRC_DIR)/core
SDL_DIR := $(SRC_DIR)/platform/SDL_uni
OUT_DIR := out

CORE_SRCS := \
    $(CORE_DIR)/Player.cpp \
    $(CORE_DIR)/Level.cpp \
    $(CORE_DIR)/GameScene.cpp \
    $(CORE_DIR)/Splash.cpp

SDL_SRCS := \
    $(SDL_DIR)/Input.cpp \
    $(SDL_DIR)/Renderer.cpp \
    $(SDL_DIR)/PlayerRender.cpp \
    $(SDL_DIR)/SplashRender.cpp


COMMON_SRCS := \
    $(SRC_DIR)/Config.cpp \
    $(SRC_DIR)/main.cpp

SRCS := $(CORE_SRCS) $(SDL_SRCS) $(COMMON_SRCS)
OBJS := $(SRCS:%.cpp=$(OUT_DIR)/%.o)

TARGET := test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OUT_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -DUSE_SDL -c $< -o $@

clean:
	rm -rf $(OUT_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)
