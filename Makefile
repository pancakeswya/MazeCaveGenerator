OS           := $(shell uname -s)

NAME         := MazeCaveGenerator

SRC_DIR      := mcg
BUILD_DIR    := build

ifeq ($(OS), Linux)
RUN          := ./$(BUILD_DIR)/$(NAME)
else
RUN          := open $(BUILD_DIR)/$(NAME).app
endif

MAKEDVI      := makeinfo --html
BUILDER      := cmake

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

dist:
	mkdir ../$(NAME)
	$(CP) * ../$(NAME)
	mv ../$(NAME) .
	$(TAR) $(NAME).tgz $(NAME)
	mv $(NAME).tgz $(HOME)/Desktop

check-style:
	find $(SRC_DIR) -name '*.cc' -o -name '*.h' | xargs clang-format -style=google -n

clean: uninstall
	$(RM) $(NAME)