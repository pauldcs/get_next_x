include .reader.mk

SRCS_OBJS := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS))

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
	@mkdir -vp $(dir $@)
	$(CC) $(CFLAGS) -o $@ -MMD -c $< -I. -g3

all: $(NAME)

$(NAME): $(SRCS_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) main.c $(SRCS_OBJS) -I.

test: all
	@bash tester/tester.sh

clean:
	rm -f $(SRCS_OBJS)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJS_DIR)
	rm -rf *.dSYM

re: fclean all

.PHONY	: all clean test fclean re