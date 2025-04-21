##
## EPITECH PROJECT, 2024
## jetpack
## File description:
## The main Makefile of our project
##

NAME_CLIENT	=	jetpack_client
NAME_SERVER	=	jetpack_server

CC		=	g++

BUILDDIR 	=	./build
SRCDIR		=	./src

SRCS		=	$(shell find $(SRCDIR) -type f -name "*.cpp")
SRCS_CLEAN	=	$(patsubst $(SRCDIR)/%, %, $(SRCS))
OBJS 		=	$(patsubst %.cpp, $(BUILDDIR)/%.o, $(SRCS_CLEAN))
OBJS_SERVER =	$(filter-out $(BUILDDIR)/client/%, $(OBJS))
OBJS_CLIENT =	$(filter-out $(BUILDDIR)/server/%, $(OBJS))


CFLAGS		=	-Werror -Wextra -std=c++20 -I./include/
DEBUGFLAGS	=	-g3 -DDEBUG_MODE
OPTIMIZEFLAGS	=	-O3
SFMFLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

.PHONY: all create-build client server debug clean fclean re \
	unit_tests tests_run doc

all: client server
	@echo -e "\033[1;32mProject compiled.\033[0m"

create-build:
	@mkdir -p $(BUILDDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(OPTIMIZEFLAGS) -c $< -o $@
	@echo -e "\033[0;33mCompiled: $< --> $@\033[0m"

client: create-build $(BUILDDIR) $(OBJS_CLIENT)
	@$(CC) $(OBJS_CLIENT) $(CFLAGS) $(OPTIMIZEFLAGS) $(SFMFLAGS) \
	-o $(NAME_CLIENT)
	@echo -e "\033[1;32m$(NAME_CLIENT) compiled.\033[0m"

server: create-build $(BUILDDIR) $(OBJS_SERVER)
	@$(CC) $(OBJS_SERVER) $(CFLAGS) $(OPTIMIZEFLAGS) -o $(NAME_SERVER)
	@echo -e "\033[1;32m$(NAME_SERVER) compiled.\033[0m"

debug: CFLAGS += $(DEBUGFLAGS)
debug: OPTIMIZEFLAGS =
debug: all

clean:
	@rm -rf $(BUILDDIR)
	@echo -e "\033[1;31mAll .o deleted.\033[0m"

fclean: clean
	@find -type f -name "*.a" -exec rm -f {} \;
	@rm -rf unit_tests*
	@rm -rf tests/unit_tests*
	@rm -rf vgcore*
	@rm -rf *.log
	@rm -rf $(NAME_CLIENT)
	@rm -rf $(NAME_SERVER)
	@echo -e "\033[1;31mProject cleaned.\033[0m"

re:	fclean all

re_debug: fclean debug

# Unit tests Makefile
unit_tests:
	@make unit_tests --no-print-directory -C./tests/

tests_run:
	@make tests_run --no-print-directory -C./tests/
	@gcovr

# Documentation
doc: tests_run
	@mkdir -p docs/html
	@mkdir -p docs/tests
	@doxygen Doxyfile
	@gcovr --branch --html-details docs/tests/test.html
	@echo -e "\033[1;33mDocumentation generated.\033[0m"
	@google-chrome docs/html/index.html
	@google-chrome docs/tests/test.html
