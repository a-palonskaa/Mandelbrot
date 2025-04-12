CC = g++
CFLAGS = -O3 -Wall -std=c++17 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations   \
		 -Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy     \
		 -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2     \
		 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked -Wpointer-arith       \
		 -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo           \
		 -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef   \
		 -Wunreachable-code -Wunused -Wvariadic-macros -Wno-literal-range 			     \
		 -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast 			 \
		 -Wno-varargs -Wstack-protector -Wsuggest-override -Wbounds-attributes-redundant \
		 -Wlong-long -Wopenmp -fcheck-new -fsized-deallocation -fstack-protector 		 \
		 -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-protector  \
		 -fPIE -Werror=vla

LDFLAGS =

INCLUDE_DIR = include
BUILD_DIR = build

SOURCES_NAIVE = naive_implementation.cpp
SOURCES_4 = optimization4.cpp
SOURCES_44 = optimization44.cpp

OBJECTS_NAIVE = $(addprefix $(BUILD_DIR)/src/, $(SOURCES_NAIVE:%.cpp=%.o))
OBJECTS_4 = $(addprefix $(BUILD_DIR)/src/, $(SOURCES_4:%.cpp=%.o))
OBJECTS_44 = $(addprefix $(BUILD_DIR)/src/, $(SOURCES_44:%.cpp=%.o))

DEPS_NAIVE = $(OBJECTS_NAIVE:%.o=%.d)
DEPS_4 = $(OBJECTS_4:%.o=%.d)
DEPS_44 = $(OBJECTS_44:%.o=%.d)

EXECUTABLE_NAIVE = build/naive
EXECUTABLE_4 = build/optimization4
EXECUTABLE_44 = build/optimization44

CFLAGS += -I$(INCLUDE_DIR) -I/opt/homebrew/include
LDFLAGS =  -L/opt/homebrew/lib  -lSDL2
LDFLAGS +=  -L./build/libs  -lcommon

all:

naive: $(EXECUTABLE_NAIVE)

$(EXECUTABLE_NAIVE): $(OBJECTS_NAIVE)
	@$(CC) $(LDFLAGS) $^ -o $@

$(OBJECTS_NAIVE): $(BUILD_DIR)/%.o:%.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MP -MMD -c $< -o $@

opt4: $(EXECUTABLE_4)

$(EXECUTABLE_4): $(OBJECTS_4)
	@$(CC) $(LDFLAGS) $^ -o $@

$(OBJECTS_4): $(BUILD_DIR)/%.o:%.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MP -MMD -c $< -o $@

opt44: $(EXECUTABLE_44)

$(EXECUTABLE_44): $(OBJECTS_44)
	@$(CC) $(LDFLAGS) $^ -o $@

$(OBJECTS_44): $(BUILD_DIR)/%.o:%.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MP -MMD -c $< -o $@


.PHONY: clean

clean:
	@rm -f $(OBJECTS) $(EXECUTABLE) $(DEPS)
