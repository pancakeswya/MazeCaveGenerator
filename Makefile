OS           := $(shell uname -s)

NAME         := MazeCaveGenerator

SRC_DIR      := src
BUILD_DIR    := build
REPORT_DIR   := report
TEST_DIR     := $(SRC_DIR)/model/test

TEST_SRC     := $(TEST_DIR)/test.cc

TEST_LIB     := gtest
TEST_NAME    := model_test
LCOV_NAME    := model_test.info

MODEL_LIB    := model
MODEL_LDLIB  := $(addprefix -l,$(MODEL_LIB))

TEST_LDLIB   := $(addprefix -l,$(TEST_LIB))

CXX          := g++
CXXFLAGS     := -Wall -Wextra -Werror -std=c++17 -I $(SRC_DIR)

GCOV         := --coverage
LCOV         := lcov --no-external -c

VALGRIND     := valgrind --tool=memcheck --trace-children=yes --track-origins=yes --leak-check=full

ifeq ($(OS), Linux)
RUN          := ./$(BUILD_DIR)/$(NAME)
OPEN         := xdg-open
else
RUN          := open $(BUILD_DIR)/$(NAME).app
OPEN         := open
endif

MAKEDVI      := makeinfo --html
CMAKE      := cmake

CP           := cp -rf
TAR          := tar cvzf
RM           := rm -rf

MAKEFLAGS    += --no-print-directory

all: install run

install:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CMAKE) .. && $(MAKE)

uninstall:
	$(RM) $(BUILD_DIR)

run:
	$(RUN)

dist:
	mkdir ../$(NAME)
	$(CP) * ../$(NAME)
	mv ../$(NAME) .
	$(TAR) $(NAME).tgz $(NAME)
	mv $(NAME).tgz $(HOME)/Desktop

$(MODEL_LIB):
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CMAKE) .. && $(CMAKE) --build . --target Model

test: $(MODEL_LIB)
	$(CXX) $(CXXFLAGS) $(TEST_SRC) -L$(BUILD_DIR) $(MODEL_LDLIB) $(TEST_LDLIB) -o $(TEST_NAME)
	./$(TEST_NAME)

gcov_report: $(MODEL_LIB)
	$(CXX) $(CXXFLAGS) $(GCOV) $(TEST_SRC) -L$(BUILD_DIR) $(MODEL_LDLIB) $(TEST_LDLIB) -o $(TEST_NAME)
	./$(TEST_NAME)
	$(LCOV) -t $(TEST_NAME) -d . -o $(LCOV_NAME)
	genhtml $(LCOV_NAME) -o $(REPORT_DIR)
	$(OPEN) $(REPORT_DIR)/index.html

check-style:
	find $(SRC_DIR) -name '*.cc' -o -name '*.h' | xargs clang-format -style=google -n

check-valgrind: test
	CK_FORK=NO $(VALGRIND) ./$(TEST_NAME)

clean: uninstall
	$(RM) $(LCOV_NAME)
	$(RM) $(REPORT_DIR)
	$(RM) *.gcno *.gcda
	$(RM) $(TEST_NAME)
	$(RM) $(NAME)