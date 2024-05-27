SRC =		main.c

HELPERS = 	free_arr.c \
			ft_arrdup.c \
			sort_arr.c \
			strjoin_and_free.c \
			is_white_space.c \
            arr_join.c

LIBFT = 	ft_strtrim.c \
			ft_strlen.c \
			ft_strdup.c \
			ft_strlcpy.c \
			ft_split.c \
			ft_strjoin.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_strchr.c \
			ft_itoa.c \
			ft_substr.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isdigit.c

UTILS =		env_utils.c \
			print_commands.c \
			print_arr.c \
			command_utils.c \
			clean_commands.c \
			print_tokens.c \
			errors.c \
			clean_data.c \
			init.c \
			init_export.c

GNL =		get_next_line_utils.c \
			get_next_line.c

LEXER =		lexer.c \
			check_separators_consecutives.c \
			handle_quotes.c \
			remove_quotes.c \
			create_commands.c \
			prepare_for_ambigous.c

EXPANSION =	expand_variables.c \
            get_var_key_len.c \
            get_variable_value.c \
            expand_variables_utils.c \
            update_content.c \
            update_content_utils.c \
            update_env_token_type.c \
            expand_heredoc.c

TOKEN =		tokenization.c \
            tokenization_utils.c \
            save_token.c \
            token_list_utils.c

PARSING =	parse_word.c \
			parse_pipe.c \
			fill_args.c \
			parse_input.c \
			remove_old_ref.c \
			parse_trunc.c \
			parse_append.c \
			parse_heredoc.c \
			parse_heredoc_utils.c \
			is_valid_filename.c \
			fill_echo_args_utils.c \
			fill_echo_args.c

HEADERS = 	minishell.h \
			colors.h \
			errors.h \
			libft.h \
			parsing.h \
			utils.h \
			tokenization.h \
			expansion.h \
			lexer.h

SRC_DIR = ./src/
HELPERS_DIR = ./src/helpers/
LIBFT_DIR = ./src/libft/
UTILS_DIR = ./src/utils/
LEXER_DIR = ./src/lexer/
TOKEN_DIR = ./src/tokenization/
GNL_DIR = ./src/GNL/
EXPANSION_DIR = ./src/expansion/
PARSING_DIR = ./src/parsing/
INC = ./includes/

HEADERS := $(addprefix $(INC), $(HEADERS))
SRC := $(addprefix $(SRC_DIR), $(SRC))
HELPERS := $(addprefix $(HELPERS_DIR), $(HELPERS))
LIBFT := $(addprefix $(LIBFT_DIR), $(LIBFT))
UTILS := $(addprefix $(UTILS_DIR), $(UTILS))
LEXER := $(addprefix $(LEXER_DIR), $(LEXER))
TOKEN := $(addprefix $(TOKEN_DIR), $(TOKEN))
EXPANSION := $(addprefix $(EXPANSION_DIR), $(EXPANSION))
PARSING := $(addprefix $(PARSING_DIR), $(PARSING))
GNL := $(addprefix $(GNL_DIR), $(GNL))
OBJS = $(SRC:.c=.o)

SRC += $(HELPERS)
SRC += $(LIBFT)
SRC += $(UTILS)
SRC += $(LEXER)
SRC += $(TOKEN)
SRC += $(GNL)
SRC += $(EXPANSION)
SRC += $(PARSING)

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
	@cc $(OBJS) $(READLINE_LIB) -fsanitize=address -o $(NAME)

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