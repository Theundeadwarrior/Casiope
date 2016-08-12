
# Config
GAME_SOURCE_DIR := Source
OBJECTS_DIR := Objects
DEPENDENCIES_DIR := Dependencies
OUTPUT_DIR := Bin

.PHONY: clean list

# Sources
CPP_FILES = $(shell find $(GAME_SOURCE_DIR)/ -type f -name '*.cpp')
OBJ_FILES = $(patsubst $(GAME_SOURCE_DIR)/%.cpp,$(OBJECTS_DIR)/%.o,$(CPP_FILES))
DEP_FILES = $(patsubst $(GAME_SOURCE_DIR)/%.cpp,$(DEPENDENCIES_DIR)/%.d,$(CPP_FILES))

# Compiler config
#CPPFLAGS += -MMD -D_LINUX_ -I$(GAME_SOURCE_DIR) -IExtern -IExtern/glm/include -std=c++11 -Werror -Wall -Wextra -Wstrict-aliasing -pedantic -Wunreachable-code -ggdb $(shell sdl2-config --cflags --libs)
CPPFLAGS += -MMD -D_LINUX_ -I$(GAME_SOURCE_DIR) -IExtern -IExtern/glm/include -std=c++11 -ggdb $(shell sdl2-config --cflags --libs)
LIBRARIES =  $(shell sdl2-config --static-libs) -lGL -lGLU -lglut -lGLEW -lGLEWmx
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPENDENCIES_DIR)/$*.Td

# Actions
COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
POSTCOMPILE = mv -f $(DEPENDENCIES_DIR)/$*.Td $(DEPENDENCIES_DIR)/$*.d
LINK = $(CXX)

# Pre-build actions
$(shell mkdir -p $(dir $(DEP_FILES)))
$(shell mkdir -p $(dir $(OBJ_FILES)))
$(shell mkdir -p $(OUTPUT_DIR))


# File building
$(OBJECTS_DIR)/%.o: $(GAME_SOURCE_DIR)/%.cpp
	$(COMPILE.cc) -o $@ $<
	$(POSTCOMPILE)

# Final targets
Game: $(OBJ_FILES)
	$(LINK) -o $(OUTPUT_DIR)/$@ $^ $(LIBRARIES)

# Helpers
list:
	@echo Sources: $(CPP_FILES)
	@echo Objects: $(OBJ_FILES)
	@echo Dependencies: $(DEP_FILES)

clean:
	rm -rf $(OBJECTS_DIR) $(DEPENDENCIES_DIR)

cleaner: clean
	rm -rf $(OUTPUT_DIR)

# Dependency stuff
$(DEPENDENCIES_DIR)/%.d: ;
.PRECIOUS: $(DEPENDENCIES_DIR)/%.d
-include $(DEP_FILES)
# DO NOT DELETE
