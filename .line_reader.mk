NAME		:= line_reader
CC			:= gcc
CFLAGS 		:= -Wall -Wextra -Werror -g3

SRCS_DIR	:= srcs
OBJS_DIR	:= .objs
INCS_DIR	:= incs

SRCS :=\
	test_main.c 			\
	utils/ft_alloc.c 		\
	utils/ft_realloc.c 		\
	utils/ft_memcpy.c 		\
	line_reader.c 			\
	reader_init.c 			\
	reader_destroy.c 		\

