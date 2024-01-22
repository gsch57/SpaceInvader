# the compiler to use
CC      = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CCFLAGS = -g -Wall -lncurses
RM      = rm -rf

NAME	= spaceInvader

SRCS 	=  

MAIN	=	main.cpp \
			src/Entity.cpp \
			src/Ncurses.cpp

OBJS	= $(SRCS:.cpp=.o)

OBJS_MAIN	= $(MAIN:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_MAIN)
	$(CC) $(CCFLAGS) -o $(NAME) $(OBJS) $(OBJS_MAIN)

clean:
	$(RM) $(OBJS) $(OBJS_MAIN)

all: clean $(MAIN)

fclean: clean
	$(RM) $(NAME)

re:	fclean all