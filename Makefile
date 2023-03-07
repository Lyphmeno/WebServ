NAME		:=	webserv

CXX			:=	c++
CXFLAGS		:=	-Wall -Wextra -Werror -std=c++98 -g3

SRCDIR		:=	srcs
SRCEXT		:=	cpp
SRC			:=	\
				./srcs/Socket.cpp\
				./srcs/SocketData.cpp\
				./srcs/SocketManager.cpp\
				./srcs/Parser.cpp\
				./srcs/Webserv.cpp\
				./srcs/Server.cpp\
				./srcs/ContentType.cpp\
				./srcs/Request.cpp\
				./srcs/Response.cpp\
				./srcs/StatusCode.cpp\
				./srcs/main.cpp\

INCDIR		:=	incs
INCEXT		:=	hpp
HEADERS		:=	\
				./incs/Location.hpp\
				./incs/Socket.hpp\
				./incs/SocketData.hpp\
				./incs/SocketManager.hpp\
				./incs/Parser.hpp\
				./incs/Server.hpp\
				./incs/Webserv.hpp\
				./incs/ContentType.hpp\
				./incs/Request.hpp\
				./incs/Response.hpp\
				./incs/StatusCode.hpp\

OBJDIR		:=	objs
OBJEXT		:=	o
OBJS		:=	$(subst $(SRCDIR),$(OBJDIR),$(SRC:.$(SRCEXT)=.$(OBJEXT)))

.PHONY: all
all: $(NAME)

$(NAME):	$(OBJDIR) $(OBJS) $(HEADERS) Makefile
			$(CXX) $(CXFLAGS) -o $(NAME) $(OBJS) 
			@echo -ne '    \033c$(E_BAR)\n'

$(OBJDIR):
			@mkdir -p $(OBJDIR)
			@$(eval $(call update_bar))

$(OBJDIR)/%.$(OBJEXT) : 	$(SRCDIR)/%.$(SRCEXT)
							@echo -ne '\033c$(E_BAR)\n'
							$(CXX) $(CXFLAGS) -c -o $@ $<  -I $(INCDIR)
							@$(eval $(call update_bar))

.PHONY: re
re: fclean all

.PHONY: clean
clean:
		@$(RM) -rf $(OBJDIR)

.PHONY: fclean
fclean: clean
		@$(RM) -rf $(NAME)

#  ---------- PROGRESS BAR ----------  #
_STOP		:=	\e[0m
_PINK		:=	\033[38;5;223m\e[1m
_ORANGE		:=	\033[38;5;209m\e[1m
VAL			:=	66
_CREAM		:=	\033[38;5;${VAL}m\e[1m
INDEX		:=	1
BUILD_SIZE	:=	$(shell find $(SRCDIR) -type f -name "*.cpp" | wc -l)
PRC			:=	$(shell echo "$(INDEX) / $(BUILD_SIZE) * 100" | bc -l)
progress	:=	$(shell echo "$(INDEX) / ($(BUILD_SIZE) / 20)" | bc -l)

define update_bar =
    E_BAR		:=	$(_PINK)-->$(_ORANGE)[$(_STOP)$(_CREAM)$(shell python3 -c 'print("█" * int($(progress)))')$(shell python3 -c 'print(" " * (20 - int($(progress))))')$(_ORANGE)]$(_PINK)<--$(_ORANGE)[$(_CREAM)$(shell echo $(PRC) / 1 | bc)%$(_ORANGE)]$(_STOP)
	INDEX		:=	$(shell echo $(INDEX) + 1 | bc -l)
    progress	:=	$(shell echo "$(INDEX) / ($(BUILD_SIZE) / 20)" | bc -l)
	PRC			:=	$(shell echo "$(INDEX) / $(BUILD_SIZE) * 100" | bc -l)
	VAL			:=	$(shell echo $(VAL) + 1 | bc -l)
	_CREAM		:=	\033[38;5;${VAL}m\e[1m
endef
#  ---------- PROGRESS BAR ----------  #
