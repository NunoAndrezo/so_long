# Executable Name
NAME			= so_long

# Directories
PRINTF		= ./printf/libftprintf.a
LIBFT		= ./libft/libft.a
LIBMLX		= ./mlx_linux/libmlx_Linux.a
INC			= include
SRC_DIR		= src
OBJ_DIR		= obj
LIBDIR_MLX	= mlx_linux

# Libraries
MLX = -L$(LIBDIR_MLX) -lmlx_Linux -lXext -lX11 -lm
# m -> Math library
# l -> Linking library
# L -> Library path
# I -> Include path

# Compiler and CFlags
CC					= cc
CFLAGS				= -Wall -Werror -Wextra -g -O3

rm					= rm -f

# Source and Object Files
SRC					=	src/flood_fill.c src/game_initialization.c src/get_next_line_utils.c \
						src/get_next_line.c src/image_utils.c src/so_long.c src/walking.c \
						src/window_utils.c src/map_checker.c src/map_to_image.c src/map_utils.c src/map_checker2.c

OBJ					=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Build rules
start:
					@make all

$(PRINTF):
					@make -C ./printf
$(LIBFT):
					@make -C ./libft
$(LIBMLX):
					@make -C ./mlx_linux

all:				$(NAME)

$(NAME):			loading_bar $(OBJ) $(PRINTF) $(LIBFT) $(LIBMLX)
					@$(CC) $(CFLAGS) $(OBJ) $(MLX) $(PRINTF) $(LIBFT) $(LIBMLX) -o $(NAME)

# Compile object files from source files
$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) -I$(INC) -I$(LIBDIR_MLX) -c $< -o $@

# Loading bar implementation
loading_bar:
					@if [ ! -f $(NAME) ] || [ "$(MAKECMDGOALS)" = "re" ]; then \
						echo "Building project..."; \
						for i in $$(seq 0 1 100); do \
							sleep 0.01; \
							printf "\rLoading: %3d%% [%-50s]" $$i $$(printf '#%.0s' $$(seq 1 $$((i / 2)))); \
						done; \
						printf "\n"; \
					else \
						echo "Nothing to be made!"; \
					fi

clean:
					@$(RM) -r $(OBJ_DIR)
					@make clean -C ./printf
					@make clean -C ./libft
					@make clean -C ./mlx_linux

fclean:				clean
					@$(RM) $(NAME)
					@make fclean -C ./printf
					@make fclean -C ./libft

re:					fclean all

# Phony targets represent actions not files
.PHONY:				start all clean fclean re loading_bar




#.PHONY specifies targets that are not actual files.
#This helps ensure that make runs these commands when specified
#even if files with these names exist.