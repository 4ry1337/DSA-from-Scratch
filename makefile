TARGET_EXEC := main
TEST_EXEC := test_runner

BUILD_DIR := ./build
SRC_DIRS := ./src

DEBUG_FLAGS := -g3 -O0
RELEASE_FLAGS := -O3 -DNDEBUG

CXXFLAGS := -Wall -Wextra -Wpedantic $(DEBUG_FLAGS)

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
TEST_SRCS := $(shell find tests -name '*.cpp')

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
TEST_OBJS := $(TEST_SRCS:%=$(BUILD_DIR)/%.o)

DEPS := $(OBJS:.o=.d) $(TEST_OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# -MMD -MP generate .d dependency files alongside .o files
CPPFLAGS := $(INC_FLAGS) -MMD -MP

.PHONY: all test lint fmt memcheck docs clean

all: $(BUILD_DIR)/$(TARGET_EXEC) compile_commands.json

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MJ $(@:.o=.json) -c $< -o $@

compile_commands.json: $(OBJS) $(TEST_OBJS)
	@printf '[\n' > $@
	@find $(BUILD_DIR) -name '*.json' | xargs cat >> $@
	@printf ']\n' >> $@

$(BUILD_DIR)/$(TEST_EXEC): $(TEST_OBJS)
	$(CXX) $(TEST_OBJS) -o $@ -lgtest -lgtest_main

test: $(BUILD_DIR)/$(TEST_EXEC)
	./$(BUILD_DIR)/$(TEST_EXEC)

lint:
	clang-tidy $(SRCS)

fmt:
	clang-format -i $(SRCS) $(shell find $(SRC_DIRS) -name '*.h')

memcheck: $(BUILD_DIR)/$(TARGET_EXEC)
	valgrind --leak-check=full ./$(BUILD_DIR)/$(TARGET_EXEC)

docs:
	doxygen

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)
