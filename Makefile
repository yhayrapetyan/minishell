SRC =		main.c

HELPERS = 	free_arr.c \
			ft_arrdup.c \
			init_export.c \
			print_arr.c \
			clean_data.c \
			ft_error.c \
			sort_arr.c \
			strjoin_and_free.c \
			init_data.c \
			fill_data_with_null.c \

LIBFT = 	ft_strtrim.c \
			ft_strlen.c \
			ft_strdup.c \
			ft_strlcpy.c \
			ft_split.c \
			ft_strjoin.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_strchr.c

ENV =		env_utils.c

LEXER =		lexer.c

HEADERS = 	minishell.h \
			colors.h \
			errors.h \
			libft.h \
			parsing.h \
			utils.h

SRC_DIR = ./src/
HELPERS_DIR = ./src/helpers/
LIBFT_DIR = ./src/libft/
ENV_DIR = ./src/env/
LEXER_DIR = ./src/lexer/
INC = ./includes/

HEADERS := $(addprefix $(INC), $(HEADERS))
SRC := $(addprefix $(SRC_DIR), $(SRC))
HELPERS := $(addprefix $(HELPERS_DIR), $(HELPERS))
LIBFT := $(addprefix $(LIBFT_DIR), $(LIBFT))
ENV := $(addprefix $(ENV_DIR), $(ENV))
LEXER := $(addprefix $(LEXER_DIR), $(LEXER))
OBJS = $(SRC:.c=.o)

SRC += $(HELPERS)
SRC += $(LIBFT)
SRC += $(ENV)
SRC += $(LEXER)

CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINE_LIB = -lreadline
NAME = minishell
RM = rm -f

BLUE   = \033[0;34m
GREEN    = \033[0;32m
RED = \033[0;31m
YELLOW  = \033[0;33m
NO_COLOR    = \033[m


SRC := $(shell printf "$(SRC)" | tr '\r' '\n')
SRC_COUNT_TOT := $(words $(SRC))
SRC_COUNT := 0
SRC_PCT = $(shell expr 100 \* $(SRC_COUNT) / $(SRC_COUNT_TOT))

all: print_info $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(READLINE_LIB) -o $(NAME)
	@printf "%b" "$(BLUE)\n$@ $(GREEN)[✓]\n"

$(OBJS): $(HEADERS) Makefile

sanitize: fclean print_info $(OBJS)
	@cc $(OBJS) -fsanitize=address -o $(NAME)

.c.o:
	@$(eval SRC_COUNT = $(shell expr $(SRC_COUNT) + 1))
	@printf "\r%18s\r$(YELLOW)[ %d/%d (%d%%) ]$(NO_COLOR)" "" $(SRC_COUNT) $(SRC_COUNT_TOT) $(SRC_PCT)
	@$(CC) $(CFLAGS) -I $(INC) -c  $< -o $(<:.c=.o)

clean: print_name
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@printf "%b" "$(BLUE)$@: $(GREEN)[✓]\n"

fclean: clean
	@$(RM) $(NAME) $(BONUS_NAME)
	@printf "%b" "$(BLUE)$@: $(GREEN)[✓]\n"

re: fclean all
	@printf "%b" "$(BLUE)$@: $(GREEN)[✓]\n"

print_info: print_name
	@printf "%b" "$(BLUE)Compiler: $(GREEN)$(CC)\n"
	@printf "%b" "$(BLUE)Name: $(GREEN)$(NAME)\n"
	@printf "%b" "$(BLUE)C Flags: $(GREEN)$(CFLAGS)\n"
	@printf "%b" "$(BLUE)Src Count: $(GREEN)$(SRC_COUNT_TOT)$(NO_COLOR)\n"


print_name:
	@printf "%b" "$(BLUE)"
	@echo "$(NAME)\n"

.PHONY: all clean fclean re sanitize print_name print_info