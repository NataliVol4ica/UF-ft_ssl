NAME = ft_ssl

HEADERS =	ft_ssl \
			structs \
			funcs \
			permutations
INCDIR = ./includes
HFILES = $(patsubst %, $(INCDIR)/%.h, $(HEADERS))

FILENAMES =	main \
			tools_struct \
			errors \
			base64 \
			base64_converters \
			des_ecb \
			des_cbc \
			parse_flags \
			des_permutations1 \
			des_permutations2 \
			des_input_conv
CFILES = $(patsubst %, $(SRCDIR)/%.c, $(FILENAMES))
OFILES = $(patsubst %, $(ODIR)/%.o, $(FILENAMES))

LIBDIR = ./libft
LIBFT = $(LIBDIR)/libft.a
FLAGS = #-Wall -Wextra -Werror -O3
LIBINCDIR = $(LIBDIR)/includes

ODIR = ./obj

BLACK = '\033[0;30m'
RED = '\033[0;31m'
GREEN = '\033[0;32m'
BROWN = '\033[0;33m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
CYAN = '\033[0;36m'
LGRAY = '\033[0;37m'
DGRAY = '\033[1;30m'
LRED = '\033[1;31m'
LGREEN = '\033[1;32m'
YELLOW = '\033[1;33m'
LBLUE = '\033[1;34m'
PINK = '\033[1;35m'
LCYAN = '\033[1;36m'
WHITE = '\033[1;37m'
NC = '\033[0m' # No Color

all: $(NAME)

$(NAME): $(ODIR) $(HFILES) $(OFILES)
	@echo ${CYAN}[Compiling the $(NAME) executable]${NC}
	gcc $(FLAGS) $(OFILES) $(LIBFT) -o $(NAME)
	@echo ${GREEN}"[========| $(NAME) is up to date. |========]"${NC}

$(ODIR)/%.o: %.c $(HFILES) $(LIBFT)
	gcc $(FLAGS) -o $@ -c $< -I$(INCDIR) -I$(LIBINCDIR)

$(ODIR):
	@mkdir -p $(ODIR)

$(LIBFT):
	@make -C $(LIBDIR)

clean:
	@echo ${RED}[Removing $(NAME) *.o files]${NC}
	@/bin/rm -rf $(ODIR)
	
fclean: clean
	@echo ${RED}[Removing executable $(NAME) file]${NC}
	@/bin/rm -f $(NAME)

re: fclean all

alias:
	alias ft_ssl="./ft_ssl"

#main: $(NAME)
#	gcc -o e -I $(INCDIR) -L. -lftprintf main.c

norm:
	@clear
	@echo ${RED}[Checking the $(NAME) NORM]${NC}
	@norminette $(CFILES) $(HFILES)
