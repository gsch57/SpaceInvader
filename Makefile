# the compiler to use
CC      = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CCFLAGS = -g -Wall -std=c++11

RM      = rm -f

NAME    = spaceInvader

MAIN    = main.cpp \
          src/Entity.cpp \
          src/Ncurses.cpp \
          src/Game.cpp \
          src/Player.cpp \
          src/EntityFactory.cpp

OBJS_MAIN = $(MAIN:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS_MAIN)
	$(CC) $(CCFLAGS) -o $(NAME) $(OBJS_MAIN) -lncurses

clean:
	$(RM) $(OBJS_MAIN)

fclean: clean
	$(RM) $(NAME)

re: fclean all
