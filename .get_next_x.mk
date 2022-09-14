NAME		:= get_next_x
CC			:= gcc
CFLAGS 		:= -Wall -Wextra -Werror -g3

SRCS_DIR	:= srcs
OBJS_DIR	:= .objs
INCS_DIR	:= incs

SRCS :=\
	test_main.c 			\
	utils/ft_alloc.c 		\
	utils/ft_realloc.c 		\
	get_next_x.c 			\
	reader_init.c 			\
	reader_destroy.c 		\

