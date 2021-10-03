CC			=	GCC
CFLAGS		=	-Wall -Wextra -Werror

CLIENT		=	client
SERVER		=	server

SRC_DIR		=	./sources/
CLIENT_DIR	=	$(SRC_DIR)client/
SERVER_DIR	=	$(SRC_DIR)server/
UTILS_DIR	=	$(SRC_DIR)utils/

LIB_DIR		=	./libft/
LIBFT		=	$(LIB_DIR)libft.a

HEADERS		=	$(LIB_DIR)includes/ ./includes/
INCLUDES	=	$(addprefix -I, $(HEADERS))

CLIENT_FILES	=	client.c

SERVER_FILES	=	server.c

UTILS_FILES		=	utils.c

CLIENT_SRC	=	$(addprefix $(CLIENT_DIR), $(CLIENT_FILES))
SERVER_SRC	=	$(addprefix $(SERVER_DIR), $(SERVER_FILES))
UTILS_SRC	=	$(addprefix $(UTILS_DIR), $(UTILS_FILES))

SERVER_OBJ	=	$(SERVER_SRC:.c=.o)
CLIENT_OBJ	=	$(CLIENT_SRC:.c=.o)
UTILS_OBJ	=	$(UTILS_SRC:.c=.o)



RM			=	rm -f
RM_DIR		=	rm -rf

RED			=	"\033[31m"
GREEN		=	"\033[32m"
YELLOW		=	"\033[33m"
RESET		=	"\033[0m"

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: all clean fclean re db

all: $(SERVER) $(CLIENT)

$(SERVER): $(LIBFT) $(SERVER_OBJ) $(UTILS_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(UTILS_OBJ) $(LIBFT) -o $(SERVER)
	@echo $(YELLOW)"@@@@@ server(exe_file) created @@@@@"$(RESET)

$(CLIENT): $(LIBFT) $(CLIENT_OBJ) $(UTILS_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(UTILS_OBJ) $(LIBFT) -o $(CLIENT)
	@echo $(YELLOW)"@@@@@ client(exe_file) created @@@@@"$(RESET)

$(LIBFT):
	@make -C $(LIB_DIR)

clean:
	$(RM) $(SERVER_OBJ)
	$(RM) $(CLIENT_OBJ)
	$(RM) $(UTILS_OBJ)
	make -C $(LIB_DIR) clean
	@echo $(RED)"REMOVE OBJECT FILES"$(RESET)

fclean: clean
	$(RM) $(SERVER)
	$(RM) $(CLIENT)
	$(RM) $(LIBFT)
	@echo $(RED)"REMOVE libft.a"$(RESET)
	@echo $(RED)"REMOVE EXECUTABLE FILES"$(RESET)

re: fclean all
