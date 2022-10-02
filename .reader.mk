NAME		:= reader
CC			:= gcc
CFLAGS 		:= -Wall -Wextra -Werror -g3

SRCS_DIR	:= srcs
OBJS_DIR	:= .objs
INCS_DIR	:= incs

SRCS :=\
	reader.c           \
	reader_utils.c     \
	reader_init.c      \
	reader_destroy.c   \

