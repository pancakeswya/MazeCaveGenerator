OS           := $(shell uname -s)

NAME         := MazeCaveGenerator

SRC_DIR      := src
BUILD_DIR    := build
LIB_DIR      := src/model
DVI_DIR      := manual
DVI_FILE     := manual.texi

ifeq ($(OS), Linux)
RUN          := ./$(BUILD_DIR)/$(NAME)
else
RUN          := open $(BUILD_DIR)/$(NAME).app
endif

MAKEDVI      := makeinfo --html
BUILDER      := cmake

LINT         := clang-format
LINT_CONF    := .clang-format
LINT_DIR     := materials/linters

CP           := cp -rf
TAR          := tar cvzf
RM           := rm -rf

MAKEFLAGS    += --no-print-directory

all: install run

install:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(BUILDER) .. && $(MAKE)

uninstall:
	$(RM) $(BUILD_DIR)

run:
	$(RUN)

dvi:
	$(MAKEDVI) $(DVI_FILE)
	$(OPEN) $(DVI_DIR)/index.html

dist:
	mkdir ../$(NAME)
	$(CP) * ../$(NAME)
	mv ../$(NAME) .
	$(TAR) $(NAME).tgz $(NAME)
	mv $(NAME).tgz $(HOME)/Desktop

check-style:
	find $(SRC_DIR) -name '*.cc' -o -name '*.h' | xargs clang-format -style=google -i

test gcov_report check-valgrind:
	mkdir -p $(LIB_DIR)/$(BUILD_DIR)
	cd $(LIB_DIR)/$(BUILD_DIR) && $(BUILDER) .. && $(MAKE) $@
.PHONY : test gcov_report check-valgrind

clean: uninstall
	$(RM) $(NAME)
	$(RM) $(LIB_DIR)/$(BUILD_DIR)