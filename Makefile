
# Config
GAME_SOURCE_DIR := Source
OBJECTS_DIR := Objects
TESTS_SOURCE_DIR := Tests
DEPENDENCIES_DIR := Dependencies
OUTPUT_DIR := Bin

.PHONY: clean list

# Sources
CPP_FILES = $(shell find $(GAME_SOURCE_DIR)/ -type f -name '*.cpp')
OBJ_FILES = $(patsubst $(GAME_SOURCE_DIR)/%.cpp,$(OBJECTS_DIR)/$(GAME_SOURCE_DIR)/%.o,$(CPP_FILES))
DEP_FILES = $(patsubst $(GAME_SOURCE_DIR)/%.cpp,$(DEPENDENCIES_DIR)/$(GAME_SOURCE_DIR)/%.d,$(CPP_FILES))
GAME_OBJ_FILES = $(shell find $(GAME_SOURCE_DIR)/Casiope -type f -name '*.cpp' | sed 's!\.cpp!.o!' | sed 's!Source/Casiope!Objects/Source/Casiope!')
TESTS_CPP_FILES = $(shell find $(TESTS_SOURCE_DIR)/ -type f -name '*.cpp')
TESTS_OBJ_FILES = $(filter-out $(GAME_OBJ_FILES),$(OBJ_FILES)) $(patsubst $(TESTS_SOURCE_DIR)/%.cpp,$(OBJECTS_DIR)/$(TESTS_SOURCE_DIR)/%.o,$(TESTS_CPP_FILES))
TESTS_DEP_FILES = $(patsubst $(TESTS_SOURCE_DIR)/%.cpp,$(DEPENDENCIES_DIR)/$(TESTS_SOURCE_DIR)/%.d,$(TESTS_CPP_FILES))

# Compiler config
CPPFLAGS += -Wno-shift-negative-value -MMD -D_LINUX_ -DLOG4CXX_STATIC -I$(GAME_SOURCE_DIR) -IExtern -IExtern/glm/include -IExtern/apache-log4cxx-0.10.0/src/main/include -std=c++14 -Werror -Wall -Wextra -Wstrict-aliasing -pedantic -Wunreachable-code -ggdb $(shell sdl2-config --cflags)
TESTFLAGS = -ITests
LIBRARIES = $(shell sdl2-config --static-libs) -lGL -lGLU -lglut -lGLEW -lGLEWmx -llog4cxx
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPENDENCIES_DIR)/$(GAME_SOURCE_DIR)/$*.Td

# Actions
COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
COMPILE_TEST.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TESTFLAGS) $(TARGET_ARCH) -c
POSTCOMPILE = mv -f $(DEPENDENCIES_DIR)/$(GAME_SOURCE_DIR)/$*.Td $(DEPENDENCIES_DIR)/$(GAME_SOURCE_DIR)/$*.d
LINK = $(CXX)

# Pre-build actions
$(shell mkdir -p $(dir $(DEP_FILES)))
$(shell mkdir -p $(dir $(OBJ_FILES)))
$(shell mkdir -p $(dir $(TESTS_DEP_FILES)))
$(shell mkdir -p $(dir $(TESTS_OBJ_FILES)))
$(shell mkdir -p $(OUTPUT_DIR))


# File building
$(OBJECTS_DIR)/$(GAME_SOURCE_DIR)/%.o: $(GAME_SOURCE_DIR)/%.cpp
	$(COMPILE.cc) -o $@ $<
	$(POSTCOMPILE)

$(OBJECTS_DIR)/$(TESTS_SOURCE_DIR)/%.o: $(TESTS_SOURCE_DIR)/%.cpp
	$(COMPILE_TEST.cc) -o $@ $<
	$(POSTCOMPILE)

# Final targets
Game: $(OBJ_FILES)
	$(LINK) -o $(OUTPUT_DIR)/$@ $^ $(LIBRARIES)

Tests: $(TESTS_OBJ_FILES)
	$(LINK) -o $(OUTPUT_DIR)/$@ $^ $(LIBRARIES)

# Helpers
list:
	@echo Sources: $(CPP_FILES)
	@echo Objects: $(OBJ_FILES)
	@echo Dependencies: $(DEP_FILES)

test-list:
	@echo Sources: $(TESTS_CPP_FILES)
	@echo Objects: $(TESTS_OBJ_FILES)
	@echo Dependencies: $(TESTS_DEP_FILES)

clean:
	rm -rf $(OBJECTS_DIR) $(DEPENDENCIES_DIR)
	rm -f $(OUTPUT_DIR)/casiope.log

cleaner: clean
	rm -f $(OUTPUT_DIR)/Game
	rm -f $(OUTPUT_DIR)/Tests

all: Game Tests

run: Game
	cd Bin; ./Game ../Data/Textures/SkyBox/front.bmp; cd ..

# Dependency stuff
$(DEPENDENCIES_DIR)/%.d: ;
.PRECIOUS: $(DEPENDENCIES_DIR)/%.d
-include $(DEP_FILES)
# DO NOT DELETE
