
NAME      		= philo

CC          	= gcc
CFLAGS      	= -Wall -Wextra -Wuninitialized -O3
# CFLAGS      	= -Wall -Wextra -Werror -Wuninitialized -O3

SRCEXT      	= c
SRCDIR      	= src
HEADERDIR		= include
OBJEXT      	= o
BUILDDIR    	= obj

LIBS			= ../lib/not_libft/bin/not_libft.a
INCLUDES		= -I$(HEADERDIR) -I../lib/
LINK			= -lpthread

OBJ_IN_DIR 		= $(BUILDDIR)/*.$(OBJEXT)

include sources.mk

OBJ	= $(foreach src,$(SRC),$(BUILDDIR)/$(notdir $(src:.$(SRCEXT)=.$(OBJEXT))))

VPATH = $(shell find $(SRCDIR) -type d | tr '\n' ':' | sed -E 's/(.*):/\1/')
.SUFFIXES:
SILECE_MAKE = | grep -v -E ".*Leaving directory|.*Entering directory"

all: ./$(NAME)

$(NAME): $(BUILDDIR)/ $(OBJ) $(HEADERDIR) $(SETTINGS)
	$(MAKE) -C ../lib/not_libft $(SILECE_MAKE)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_IN_DIR) $(LIBS) -o $(NAME) $(LINK)

# sources

$(BUILDDIR)/%.$(OBJEXT): %.$(SRCEXT) $(HEADERDIR) $(SETTINGS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(BUILDDIR)/$(notdir $@) $(LINK)

clean:
ifneq ($(BUILDDIR),.)
	/bin/rm -rf $(BUILDDIR)/
endif

fclean:
	$(MAKE) clean $(SILECE_MAKE)
	/bin/rm -f $(NAME)

re:
	$(MAKE) fclean $(SILECE_MAKE)
	$(MAKE) all $(SILECE_MAKE)

$(BUILDDIR)/:
	mkdir -p $(BUILDDIR)

findsources:
	echo "# SRC = \$$(shell find $(SRCDIR) -type f -name '*.c')" > sources.mk
	echo "SRC = \\" >> sources.mk
	find src/ -name "*.c" -exec echo "{} \\" \; >> sources.mk

silent:
	@$(MAKE) > /dev/null

eval1:
	@echo "THE PHILOSOPHER SHOULD NOT EAT AND SHOULD DIE"
	./$(NAME) 1 800 200 200

eval2:
	@echo "NO ONE SHOULD DIE"
	./$(NAME) 5 800 200 200

eval3:
	@echo "NO ONE SHOULD DIE AND THE SIMULATION SHOULD STOP WHEN ALL THE \
PHILOSOPHER HAS EATEN AT LEAST 7 TIMES EACH"
	./$(NAME) 5 800 200 200 7 | grep eating | wc -l

eval4:
	@echo "NO ONE SHOULD DIE"
	./$(NAME) 4 410 200 200

eval5:
	@echo "A PHILOSOPHER SHOULD DIE"
	./$(NAME) 4 310 200 100


.PHONY: all clean fclean re findsources silent
