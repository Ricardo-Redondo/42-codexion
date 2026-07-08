NAME        = codexion

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -pthread
INC         = -I includes/

SRC_DIR     = srcs/
OBJ_DIR     = obj/

SRC_FILES   = main.c parser.c utils.c sync_utils.c sim.c monitor.c \
              safe_functions.c init_sim.c getter_setter.c write.c \
			  clean.c dongle.c safe_functions2.c heap.c

SRCS        = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS        = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))


all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(INC) -o $(NAME)
	@printf "Codexion is compiled.\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@printf "Objects removed.\n"

fclean: clean
	@rm -f $(NAME)
	@printf "all removed.\n"

re: fclean all

.PHONY: all clean fclean re