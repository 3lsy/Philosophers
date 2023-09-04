# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/25 11:47:33 by echavez-          #+#    #+#              #
#    Updated: 2023/09/01 19:39:52 by echavez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        =   philo

#****************** INC *******************#
# General
INC         =   ./include/                  # Project header files drectory

INCLUDE     =   -O3 -I $(INC)

#****************** SRC *******************#

DIRSRC      =   ./src/
DIRFOO      :=  $(DIRSRC)utils/

DIRS        :=  $(DIRSRC) $(DIRFOO)

SRC         =   main.c parser.c fork.c philosopher.c actions.c lamuerte.c
FOO         =	ft_strlen.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_perror.c ft_isdigit.c ft_isint.c ft_atoi.c ft_strcmp.c

SRCS        :=  $(SRC) $(FOO)

#***************** DEPS ******************#

DIROBJ      =   ./depo/

#********************************* END OF CONFIG *********************************#

OAUX        =   $(SRCS:%=$(DIROBJ)%)
DEPS        =   $(OAUX:.c=.d)
OBJS        =   $(OAUX:.c=.o)

.ONESHELL:
$(shell mkdir -p $(DIROBJ))

ifdef FLAGS
    ifeq ($(FLAGS), no)
CFLAGS      =
    endif
    ifeq ($(FLAGS), debug)
CFLAGS      =   -Wall -Wextra -Werror -ansi -pedantic -g -fsanitize=address
    endif
else
CFLAGS      =   -Wall -Wextra -Werror
endif

ifdef VERB
    ifeq ($(VERB), on)
CFLAGS      +=  -DM_VERB
    endif
endif

ifndef VERBOSE
.SILENT:
endif

ENV         =   /usr/bin/env
CC          =   $(ENV) clang
RM          =   $(ENV) rm -rf
ECHO        =   $(ENV) echo -e
MKDIR       =   $(ENV) mkdir -p
GIT         =   $(ENV) git
BOLD        =   "\e[1m"
REVER       =   "\e[7m"
BLINK       =   "\e[5m"
RED         =   "\e[38;2;255;0;0m"
GREEN       =   "\e[92m"
BLUE        =   "\e[34m"
YELLOW      =   "\e[33m"
E0M         =   "\e[0m"

FMT         :=  $(REVER)$(YELLOW)$(BLINK)

#******************************* DEPS COMPILATION ********************************#

define generate_objects
$(DIROBJ)%.o    :   $(1)%.c
	                @printf $(GREEN)"Generating $(NAME) objects... %-33.33s\r"$(E0M) $$@
	                @$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $$@ -c $$<
endef

# Generate objects
$(foreach dir,$(DIRS),$(eval $(call generate_objects,$(dir))))

#******************************* MAIN COMPILATION ********************************#

$(NAME)         :   $(OBJS)
	                @$(CC) $(INCLUDE) $(CFLAGS) -o $(NAME) $(OBJS)
	                @$(ECHO)
	                @$(ECHO) '                       '$(FMT)'██████'$(E0M)
	                @$(ECHO) '                   '$(FMT)'████░░░░░░██'$(E0M)
	                @$(ECHO) '                 '$(FMT)'██░░░░░░░░██'$(E0M)
	                @$(ECHO) '               '$(FMT)'██░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) '             '$(FMT)'██░░░░░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) '           '$(FMT)'██░░░░░░░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) '           '$(FMT)'██░░░░░░░░░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) '   '$(FMT)'████████░░░░░░░░░░░░░░░░░░░░░░░░████████'$(E0M)
	                @$(ECHO) ' '$(FMT)'██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) ' '$(FMT)'██▓▓░░░░░░░░░░░░  ██░░░░  ██░░░░░░░░░░░░▓▓██'$(E0M)
	                @$(ECHO) '   '$(FMT)'██▓▓░░░░░░░░░░████░░░░████░░░░░░░░░░▓▓██'$(E0M)
	                @$(ECHO) '     '$(FMT)'██▓▓░░░░░░░░████░░░░████░░░░░░░░▓▓██'$(E0M)
	                @$(ECHO) '       '$(FMT)'██░░░░░░░░▓▓██░░░░██▓▓░░░░░░░░██'$(E0M)
	                @$(ECHO) '       '$(FMT)'██░░░░░░░░░░░░░░░░░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) '       '$(FMT)'██░░░░░░░░░░░░░░░░░░░░░░░░░░░░██'$(E0M)
	                @$(ECHO) '       '$(FMT)'██▓▓░░░░░░░░░░░░░░░░░░░░░░░░▓▓██'$(E0M)
	                @$(ECHO) '       '$(FMT)'██▓▓░░░░░░░░░░░░░░░░░░░░░░░░▓▓██'$(E0M)
	                @$(ECHO) '         '$(FMT)'██░░░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░██'$(E0M)
	                @$(ECHO) '         '$(FMT)'██▓▓░░▓▓████████████▓▓░░▓▓██'$(E0M)
	                @$(ECHO) '           '$(FMT)'██▓▓██'$(E0M)'            '$(FMT)'██▓▓██'$(E0M)
	                @$(ECHO) '             '$(FMT)'██'$(E0M)'                '$(FMT)'██'$(E0M)
	                @$(ECHO) $(E0M)
	                @$(ECHO) $(BOLD)$(GREEN)'> '$(NAME)' Compiled'$(E0M)

$(OBJS): | mkdepo

clean           :
	                @($(RM) $(OBJS))
	                @($(RM) $(DEPS))
	                @($(RM) $(DIROBJ))
	                @$(ECHO) $(BOLD)$(RED)'> '$(NAME)' directory        cleaned'$(E0M)

all             :       $(NAME)

fclean          :       clean
	                @$(RM) $(NAME)
	                @$(ECHO) $(BOLD)$(RED)'> Executable             removed'$(E0M)


re              :  fclean mkdepo all

mkdepo			:
					@$(MKDIR) $(DIROBJ)

init            :
	                @$(GIT) submodule init
	                @$(GIT) submodule update

.PHONY          :       all clean re fclean

-include $(DEPS)
