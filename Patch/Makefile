# Color Aliases
DEFAULT	= \033[0;39m
GREEN	= \033[0;92m
BLUE	= \033[0;94m
CYAN	= \033[0;96m
RED		= \033[0;91m

# Make variables
CC			= cc
CFLAGS		= -Wextra -Werror -Wall
RM			= rm -f

INC	= minishell.h
LIBFT = -L libft -lft


NAME = minishell

BUILTIN = ft_cd ft_echo ft_env ft_exit ft_export ft_pwd ft_unset

CMD = cmd_list cmd_utils get_cmd

ENV = ft_split2 handle_envp hashmap hashmap2 hashmaplist

EXECUTE = execute execute_utils is_cmd_present launch pipes shlvl

SIGNALS = signals

TOKENIZER = handle_dollar order_check token_list tokenize utils

MAIN = minishell

SRC = $(addsuffix .c, $(addprefix builtin/, $(BUILTIN))) \
	  $(addsuffix .c, $(addprefix cmd/, $(CMD))) \
	  $(addsuffix .c, $(addprefix env/, $(ENV))) \
	  $(addsuffix .c, $(addprefix execute/, $(EXECUTE))) \
	  $(addsuffix .c, $(addprefix signals/, $(SIGNALS))) \
	  $(addsuffix .c, $(addprefix tokenizer/, $(TOKENIZER))) \
	  $(addsuffix .c, $(MAIN)) \

OBJ = $(SRC:%.c=%.o)

# Make Commands
all:	$(NAME)

$(NAME):  $(OBJ)
	@printf "\n$(BLUE)Compiling $(NAME)...$(DEFAULT)"
	@make -C libft/
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
	@printf "\n$(GREEN)Ready!\n$(DEFAULT)"

%.o:	%.c
	@printf "$(BLUE)Generation $(CYAN)%-33.33s\r$(DEFAULT)" $@
	@$(CC) $(CFLAGS) -c $< -o $@
clean:
	@make clean -C libft/
	@printf "$(RED)Cleaning up object files in libft...$(DEFAULT)\n"
	@$(RM) $(OBJ)
	@printf "$(RED)Cleaning up object files in $(NAME)...$(DEFAULT)\n"

fclean:		clean
	@make fclean -C libft/
	@printf "$(RED)Removed libft$(DEFAULT)\n"
	@$(RM) $(NAME)
	@printf "$(RED)Removed $(NAME)$(DEFAULT)\n"

re:			fclean all

.PHONY:	all clean fclean re
