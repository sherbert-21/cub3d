cmake_minimum_required(VERSION 3.17)
project(cub3d C)

set(CMAKE_C_STANDARD 11)

include_directories(include)
include_directories(libft)
include_directories(mlx)

add_executable(${PROJECT_NAME}
    libft/ft_atoi.c
    libft/ft_bzero.c
    libft/ft_calloc.c
    libft/ft_isalnum.c
    libft/ft_isalpha.c
    libft/ft_isascii.c
    libft/ft_isdigit.c
    libft/ft_isprint.c
    libft/ft_itoa.c
    libft/ft_lstadd_back.c
    libft/ft_lstadd_front.c
    libft/ft_lstclear.c
    libft/ft_lstdelone.c
    libft/ft_lstiter.c
    libft/ft_lstlast.c
    libft/ft_lstmap.c
    libft/ft_lstnew.c
    libft/ft_lstsize.c
    libft/ft_memccpy.c
    libft/ft_memchr.c
    libft/ft_memcmp.c
    libft/ft_memcpy.c
    libft/ft_memmove.c
    libft/ft_memset.c
    libft/ft_putchar_fd.c
    libft/ft_putendl_fd.c
    libft/ft_putnbr_fd.c
    libft/ft_putstr_fd.c
    libft/ft_split.c
    libft/ft_strchr.c
    libft/ft_strdup.c
    libft/ft_strjoin.c
    libft/ft_strlcat.c
    libft/ft_strlcpy.c
    libft/ft_strlen.c
    libft/ft_strmapi.c
    libft/ft_strncmp.c
    libft/ft_strnstr.c
    libft/ft_strrchr.c
    libft/ft_strtrim.c
    libft/ft_substr.c
    libft/ft_tolower.c
    libft/ft_toupper.c
        src/utils/create_bmp.c
        src/parse/parse_ceilling_floor_color.c
        src/main.c
    src/error.c
        src/utils/gnl.c
        src/init.c
        src/render.c
        src/move.c
    src/player.c
    src/ray.c
        src/screen.c
        src/parse/parse_texture.c
    src/texturisation.c
        src/utils/gnl_utils.c
        src/parse/valid_input.c
    src/turn.c
    src/sprite.c
    src/draw_sprite.c src/parse/parse_file.c src/parse/parse_info_fields.c src/utils/utils.c src/parse/parse_map.c)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )

target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
target_link_libraries(${PROJECT_NAME} "-framework AppKit")
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/mlx/libmlx.a)
