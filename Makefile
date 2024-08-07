# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 13:57:13 by dkremer           #+#    #+#              #
#    Updated: 2024/08/07 17:21:37 by dkremer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the binary
NAME     = philo

# Compiler and flags
CC       = cc
CFLAGS   = -Wall -Werror -Wextra -Iincludes -g3 -o3
LDFLAGS = -lpthread

# Source and object directories
BINDIR   = bin

# Source files
SRCS     = error.c init.c main.c monitoring.c threading.c utils.c work.c

# Object files
OBJS     = $(SRCS:./%.c=$(BINDIR)/%.o)

# Default target
all: $(NAME)

.SILENT:

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)
	echo $(GREEN)"Building $(NAME)"$(DEFAULT);

# Rule to compile source files to object files in the bin directory
$(BINDIR)/%.o: ./%.c | $(BINDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create the bin directory if it does not exist
$(BINDIR):
	mkdir -p $(BINDIR)

# Remove all object files
clean:
	rm -f $(BINDIR)/*.o
	echo $(RED)"Removing $(NAME) object files"$(DEFAULT);

# Remove all files
fclean: clean
	rm -f $(NAME)
	rm -rf $(BINDIR)
	echo $(RED)"Removing $(NAME)"$(DEFAULT);

# Rebuild everything
re: fclean all
	echo $(GREEN)"Rebuilding everything"$(DEFAULT);

.PHONY: all clean fclean re

# Colours
DEFAULT = "\033[39m"
GREEN   = "\033[32m"
RED     = "\033[31m"
