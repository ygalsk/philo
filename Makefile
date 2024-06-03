# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkremer <dkremer@student.42heilbronn.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 13:57:13 by dkremer           #+#    #+#              #
#    Updated: 2024/06/03 17:04:59 by dkremer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the binary
NAME     = philo

# Compiler and flags
CC       = cc
CFLAGS   = -Wall -Werror -Wextra -g

# Source and object directories
BINDIR   = bin

# Source files
SRCS     = $(wildcard ./*.c)

# Object files
OBJS     = $(SRCS:./%.c=$(BINDIR)/%.o)

# Default target
all: $(NAME)

.SILENT:

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	echo $(GREEN)"Building $(NAME)"$(DEFAULT);

# Rule to compile source files to object files in the bin directory
$(BINDIR)/%.o: ./%.c | $(BINDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Update Submodule

submodule:
	git submodule update --init --recursive

# Create the bin directory if it does not exist
$(BINDIR):
	mkdir -p $(BINDIR)

# Remove all object files
clean:
	rm -f $(BINDIR)/*.o
	make -C libft clean
	echo $(RED)"Removing $(NAME) object files"$(DEFAULT);

# Remove all files
fclean: clean
	rm -f $(NAME)
	rm -rf $(BINDIR)
	make -C libft fclean
	echo $(RED)"Removing $(NAME)"$(DEFAULT);

# Rebuild everything
re: fclean all
	echo $(GREEN)"Rebuilding everything"$(DEFAULT);

.PHONY: all clean fclean re

# Colours
DEFAULT = "\033[39m"
GREEN   = "\033[32m"
RED     = "\033[31m"
