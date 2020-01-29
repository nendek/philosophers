
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

NAME = philo_one
FILES = main.c utils.c

SRCS_DIR = srcs
SRCS = $(addprefix $(SRCS_DIR)/,$(FILES))

INCS_DIR = includes
INCS = -I $(INCS_DIR)

OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/,$(FILES:%.c=%.o))

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
		$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS)

$(OBJS_DIR):
		mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
		$(CC) $(CFLAGS) $(INCS) -c -o $@ $<
.PHONY: clean
clean:
		rm -rf objs

.PHONY: fclean
fclean: clean
		rm -f $(NAME)

.PHONY: re
re: fclean all
