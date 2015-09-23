#include "ft_select.h"
#include "libft.h"

int 	sign(void)
{
  handle_winch();
  handle_sigcont();
  return (1);
}

int ft_init(void)
{
	char            *name_term;
	struct termios  term;

	if (!(name_term = getenv("TERM")))
		return (0);
	tgetent(NULL, name_term);
	if (tcgetattr(0, &term) == -1)
		return (0);
	ft_memcpy(&ft_glob(NULL)->sauv, &term, sizeof(struct termios));
	get_canon(term);
	stat_cursor(0);
	sign(); // handle_signal
	get_new_size(0); // handle_winch
	return (1);
}

int             main(int argc, char **argv)
{
	t_select        *info;

	(void)argc;
	if (!(info = (t_select *)malloc(sizeof(t_select))) ||
		!(ft_glob(info)) ||
		(ft_out_fd() == -1) ||
		!(ft_glob(NULL)->list = ft_parse(++argv)) ||
		!ft_init())
		return (0);
	looping();
}