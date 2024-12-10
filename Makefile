SRC =		main.c \

HELPERS = 	free_arr.c \
			ft_arrdup.c \
			sort_arr.c \
			strjoin_and_free.c \
			is_white_space.c \
            arr_join.c


BUILTIN =	builtin_utils_norm.c \
			builtin_utils.c \
			builtin.c \
			cd_norm.c \
			cd_utils_norm.c \
			cd_utils.c \
			cd_validation.c \
			cd.c \
			echo.c \
			env.c \
			exit_validation.c \
			exit.c \
			export_norm.c \
			export_utils_norm.c \
			export_utils.c \
			export_validation.c \
			export.c \
			pwd.c \
			unset.c \
			unset_utils_norm.c \

EXECUTION = execute.c \
			get_path.c \
			get_path_utils.c \
			handle_descriptors.c \
			execute_utils.c \
			pipe_utils.c \
			reset_descriptors.c \
			execute_command.c

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
			ft_isdigit.c \
			ft_memset.c \
			ft_strstr.c \
			ft_atoi.c

UTILS =		env_utils.c \
			print_arr.c \
			command_utils.c \
			clean_commands.c \
			errors.c \
			clean_data.c \
			init.c \
			init_export.c \
			start_minishell.c \
			signals.c \
			signals_utils.c

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
            token_list_utils.c \
			join_tokens.c \
			rm_empty_tokens.c

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
			fill_echo_args.c \
			fill_args_utils.c

HEADERS = 	minishell.h \
			colors.h \
			errors.h \
			libft.h \
			parsing.h \
			utils.h \
			tokenization.h \
			expansion.h \
			lexer.h \
			execution.h \
			builtin.h

SRC_DIR = ./src/
HELPERS_DIR = ./src/helpers/
LIBFT_DIR = ./src/libft/
UTILS_DIR = ./src/utils/
LEXER_DIR = ./src/lexer/
TOKEN_DIR = ./src/tokenization/
EXPANSION_DIR = ./src/expansion/
PARSING_DIR = ./src/parsing/
EXECUTION_DIR = ./src/execution/
BUILTIN_DIR = ./src/builtin/
HEADERS_DIR = ./includes/
OBJS_DIR = ./obj/

READLINE_DIR = readline_local


HEADERS := $(addprefix $(HEADERS_DIR), $(HEADERS))
READLINE_HEADERS := $(addprefix ./$(READLINE_DIR), /include)
SRC := $(addprefix $(SRC_DIR), $(SRC))
HELPERS := $(addprefix $(HELPERS_DIR), $(HELPERS))
LIBFT := $(addprefix $(LIBFT_DIR), $(LIBFT))
UTILS := $(addprefix $(UTILS_DIR), $(UTILS))
LEXER := $(addprefix $(LEXER_DIR), $(LEXER))
TOKEN := $(addprefix $(TOKEN_DIR), $(TOKEN))
EXPANSION := $(addprefix $(EXPANSION_DIR), $(EXPANSION))
PARSING := $(addprefix $(PARSING_DIR), $(PARSING))
EXECUTION := $(addprefix $(EXECUTION_DIR), $(EXECUTION))
BUILTIN := $(addprefix $(BUILTIN_DIR), $(BUILTIN))
READLINE_PATH := $(addprefix $(shell pwd)/, $(READLINE_DIR))

SRC += $(HELPERS)
SRC += $(LIBFT)
SRC += $(UTILS)
SRC += $(LEXER)
SRC += $(TOKEN)
SRC += $(EXPANSION)
SRC += $(PARSING)
SRC += $(EXECUTION)
SRC += $(BUILTIN)


ifeq ($(shell uname -s), Darwin)
	READLINE_LIB =  -L$(READLINE_DIR) -lreadline
else
	READLINE_LIB =  -lreadline
endif

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = minishell
RM = rm -rf

BLUE   = \033[0;34m
GREEN    = \033[0;32m
RED = \033[0;31m
YELLOW  = \033[0;33m
NO_COLOR    = \033[m

SRC := $(shell printf "$(SRC)" | tr '\r' '\n')
SRC_COUNT_TOT := $(words $(SRC))
SRC_COUNT := 0
SRC_PCT = $(shell expr 100 \* $(SRC_COUNT) / $(SRC_COUNT_TOT))

OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJS_DIR)%.o, $(SRC))

all: print_info $(NAME)

install:
	@if [ ! -d ./$(READLINE_DIR) ]; then \
		curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz; \
		tar -xpf readline-8.2.tar.gz; \
		rm -rf readline-8.2.tar.gz; \
		mkdir -p ./${READLINE_DIR}; \
		cd readline-8.2; \
		./configure --prefix="${READLINE_PATH}"; \
		make; \
		make install; \
		rm -rf ../readline-8.2; \
	fi

$(NAME): $(OBJS)
	@${CC} ${CFLAGS} -I $(HEADERS_DIR) -I $(READLINE_HEADERS)  ${OBJS} $(READLINE_LIB)  -o ${NAME}
	@printf "%b" "$(BLUE)\n$@ $(GREEN)[✓]$(NO_COLOR)\n"

$(OBJS): $(HEADERS) Makefile

sanitize: fclean print_info $(OBJS)
	@cc $(OBJS) ./$(READLINE_LIB)/ -fsanitize=address -o $(NAME)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(eval SRC_COUNT = $(shell expr $(SRC_COUNT) + 1))
	@printf "\r%18s\r$(YELLOW)[ %d/%d (%d%%) ]$(NO_COLOR)" "" $(SRC_COUNT) $(SRC_COUNT_TOT) $(SRC_PCT)
	@$(CC) $(CFLAGS)  -I $(HEADERS_DIR) -I $(READLINE_HEADERS) -c $< -o $@

clean: print_name
	@$(RM) $(OBJS_DIR)
	@printf "%b" "$(BLUE)$@: $(GREEN)[✓]$(NO_COLOR)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "%b" "$(BLUE)$@: $(GREEN)[✓]$(NO_COLOR)\n"

uninstall:
	@$(RM) readline-8.2
	@$(RM) readline_local

re: fclean all
	@printf "%b" "$(BLUE)$@: $(GREEN)[✓]$(NO_COLOR)\n"

print_info: print_name
	@printf "%b" "$(BLUE)Compiler: $(GREEN)$(CC)\n"
	@printf "%b" "$(BLUE)Name: $(GREEN)$(NAME)\n"
	@printf "%b" "$(BLUE)C Flags: $(GREEN)$(CFLAGS)\n"
	@printf "%b" "$(BLUE)Src Count: $(GREEN)$(SRC_COUNT_TOT)$(NO_COLOR)\n"

print_name:
	@printf "%b" "$(BLUE)"
	@echo "$(NAME)$(NO_COLOR)\n"

.PHONY: all clean fclean re sanitize print_name print_info install uninstall