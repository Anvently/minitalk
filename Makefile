NAME		=	minitalk
SERVER		=	server
CLIENT		=	client
BONUS_NAME	=

INCLUDES	=	includes/
SRCS_FOLDER	=	srcs/
OBJS_FOLDER	=	objs/

SRCS_FILES	=	error.c

OBJS		=	$(addprefix $(OBJS_FOLDER),$(SRCS_FILES:.c=.o))
SRCS		=	$(addprefix $(SRCS_FOLDER),$(SRCS_FILES))

LIBFT		=	libft/libft.a

DEPS		=	$(LIBFT) $(INCLUDES)$(NAME).h $(INCLUDES)libft.h Makefile

STATIC_LINK	=	-Llibft/ -lft -lreadline

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3 -I$(INCLUDES)

.PHONY		=	all clean fclean test re bonus

all: $(SERVER) $(CLIENT)

$(SERVER): $(LIBFT) $(OBJS) $(OBJS_FOLDER)server.o
	@echo "\n-----COMPILING $(SERVER)-------\n"
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_FOLDER)server.o $(STATIC_LINK) -o $(SERVER)
	@echo "Server has been successfully created."

$(CLIENT): $(LIBFT) $(OBJS) $(OBJS_FOLDER)client.o
	@echo "\n-----COMPILING $(CLIENT)-------\n"
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_FOLDER)client.o $(STATIC_LINK) -o $(CLIENT)
	@echo "Client has been successfully created."

bonus: $(BONUS_NAME)

$(OBJS_FOLDER)%.o: $(SRCS_FOLDER)%.c $(DEPS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(INCLUDES)libft.h: libft/libft.h
	@echo "------ UPDATING LIBFT HEADER -------\n"
	cp libft/libft.h includes/libft.h

$(LIBFT): $(INCLUDES)libft.h
	@echo "\n-------COMPILING LIBFT--------------\n"
	make -C libft/
	make clean -C libft/
	@echo "\n\n"

clean:
	@echo "\n-------------CLEAN--------------\n"
	make clean -C libft/
	rm -rf $(OBJS_FOLDER)
	@echo "object files have been removed."

fclean: clean
	@echo "\n-------------FORCE CLEAN--------------\n"
	make fclean -C libft/
	rm -rf $(NAME) $(BONUS_NAME) $(SERVER) $(CLIENT)
	@echo "$(NAME) and object files have been removed."

re: fclean all
