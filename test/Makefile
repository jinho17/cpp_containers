NAME = container
FLAG =	-Wall -Wextra -Werror -std=c++98
HEADER = -I../
CC = clang++
SRCS =	main.cpp test_list.cpp test_vector.cpp test_map.cpp test_stack.cpp test_queue.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAG) $(HEADER) $^ -o $(NAME)


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all