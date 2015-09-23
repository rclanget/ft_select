#include "ft_select.h"
#include "libft.h"

int ft_exit(void)
{
  set_term(*ft_glob(NULL)->sauv);
  stat_cursor(1);
  free_list(ft_glob(NULL)->list);
  free(ft_glob(NULL));
  exit (0);
}

int ft_putch(int c)
{
  return (write(ft_glob(NULL)->out_fd, &c, 1));
}

void print_video(char *str)
{
  char buf[30];
  char *ap;
  char *standout;
  char *stendout;

  ap = buf;
  standout = tgetstr("so", &ap);
  stendout = tgetstr("se", &ap);
  ft_putstr_fd(standout, ft_glob(NULL)->out_fd);
  ft_putstr_fd(str, ft_glob(NULL)->out_fd);
  ft_putstr_fd(stendout, ft_glob(NULL)->out_fd);
}

void print_underline(char *str)
{
  char buf[30];
  char *ap;
  char *standout;
  char *stendout;

  ap = buf;
  standout = tgetstr("us", &ap);
  stendout = tgetstr("ue", &ap);
  ft_putstr_fd(standout, ft_glob(NULL)->out_fd);
  ft_putstr_fd(str, ft_glob(NULL)->out_fd);
  ft_putstr_fd(stendout, ft_glob(NULL)->out_fd);
}

void print_underline_video(char *str)
{
  char buf[30];
  char *ap;
  char *standout_v;
  char *stendout_v;
  char *standout;
  char *stendout;

  ap = buf;
  standout = tgetstr("us", &ap);
  stendout = tgetstr("ue", &ap);
  standout_v = tgetstr("so", &ap);
  stendout_v = tgetstr("se", &ap);
  ft_putstr_fd(standout, ft_glob(NULL)->out_fd);
  ft_putstr_fd(standout_v, ft_glob(NULL)->out_fd);
  ft_putstr_fd(str, ft_glob(NULL)->out_fd);
  ft_putstr_fd(stendout, ft_glob(NULL)->out_fd);
  ft_putstr_fd(stendout_v, ft_glob(NULL)->out_fd);
}

void print_file(t_lst *lst)
{
  if (lst->slctd)
  {
    if (lst->crrnt)
      print_underline_video(lst->file);
    else
      print_video(lst->file);
  }
  else if (lst->crrnt)
    print_underline(lst->file);
  else
    ft_putstr_fd(lst->file, ft_glob(NULL)->out_fd);
}

void put_cursor(int i, int j)
{
  char buf[30];
  char *ap = buf;
  char *gotostr;

  gotostr = tgetstr("cm", &ap);
  ft_putstr_fd(tgoto(gotostr, j, i), ft_glob(NULL)->out_fd);
}

void print_elem(t_lst *list)
{
  int i;
  int j;
  t_lst *begin;
  int current;

  i = 1;
  j = 0;
  current = 0;
  begin = list;
  clear_win();
  while (1)
  {
    if (begin->crrnt)
        current = 1;
    if ((i == ft_glob(NULL)->line) && (j += (ft_glob(NULL)->maxlen + 1)))
        i = 0;
    if (!begin->dlted)
    {
      print_file(begin);
      put_cursor(i++, j);
    }    
    if ((j + ft_glob(NULL)->maxlen) > ft_glob(NULL)->col)
      break;
    begin = begin->next;
    if (begin->start)
      break;
  }
  if (!current)
    print_elem(begin->next);
  put_cursor(ft_glob(NULL)->line + 1, 0);
}

int             main(int argc, char **argv)
{
	char            *name_term;
  struct termios  term;
  struct termios  sauv;
  t_select        *info;

  (void)argc;
  handle_winch();
  handle_sigcont();
  info = (t_select *)malloc(sizeof(t_select));
  ft_glob(info);
  if (ft_out_fd() == -1)
    exit(0);
  if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	tgetent(NULL, name_term);
  ft_glob(NULL)->list = ft_parse(argv);
	if (tcgetattr(0, &sauv) == -1)
  	return (-1);
  term = sauv;
  ft_glob(NULL)->sauv = &sauv;
  get_canon(term);
  stat_cursor(0);
  get_size();
  print_elem(ft_glob(NULL)->list);
  while (1)
    looping();
}