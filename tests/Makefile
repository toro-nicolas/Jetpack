##
## EPITECH PROJECT, 2024
## Unit tests
## File description:
## The Makefile of the unit tests
##

NAME		=	unit_tests

SRCS		+=	`find ../src -type f -name "*.c" -not -name "main.cpp" \
			| tr '\n' ' '`

TESTS		=	`find . -type f -name "*.c" | tr '\n' ' '`

CC		=	gcc

CFLAGS		=	-Werror -Wextra
CFLAGS		+=	-I../include/
CFLAGS		+= 	--coverage -lcriterion -lgcov

.PHONY: all clean fclean tests_run

all: $(NAME)

clean:
	@rm -rf *.gcda
	@rm -rf *.gcno
	@echo -e "\033[1;31mUnit tests deleted.\033[0m"

fclean:	clean
	@rm -rf $(NAME)
	@rm -rf ../$(NAME)

$(NAME): fclean
	@$(CC) -o $(NAME) $(TESTS) $(SRCS) $(CFLAGS) $(LDFLAGS)
	@cp $(NAME) ../
	@echo -e "\033[1;33mUnit tests created.\033[0m"

tests_run: $(NAME)
	@echo -e "\033[1;32mExecuting unit tests and gcovr...\033[0m"
	@./$(NAME)
