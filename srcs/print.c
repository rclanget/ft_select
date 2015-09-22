#include "ft_select.h"
#include "libft.h"

int ft_putch(int c)
{
  return (write(1, &c, 1));
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
  tputs(standout, 1, ft_putch);
  tputs(str, 1, ft_putch);
  tputs(stendout, 1, ft_putch);
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
  tputs(standout, 1, ft_putch);
  tputs(str, 1, ft_putch);
  tputs(stendout, 1, ft_putch);
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
  tputs(standout_v, 1, ft_putch);
  tputs(standout, 1, ft_putch);
  tputs(str, 1, ft_putch);
  tputs(stendout, 1, ft_putch);
  tputs(stendout_v, 1, ft_putch);
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
    tputs(lst->file, 1, ft_putch);
}

void put_cursor(int i, int j)
{
  char buf[30];
  char *ap = buf;
  char *gotostr;

  gotostr = tgetstr("cm", &ap);
  tputs(tgoto(gotostr, j, i), 1, ft_putch);
}

// int  nbr_line(t_select *elem)
// {
//   int nb_elem;
//   int nb_col;

//   i = 0;
//   elem->list = elem->list->next;
//   while (!elem->list->start && i++)
//     elem->list = elem->list->next;
//   nb_col = i / ft_glob(NULL)->line;
//   if (((i + 1) * ft_glob(NULL)->maxlen) < ft_glob(NULL)->col)


//   if ()
// }

void print_elem(t_select *elem)
{
  int i;
  int j;
  t_lst *begin;

  i = 1;
  j = 0;
  begin = elem->list;
  clear_win();
  while (1)
  {
    if ((i == ft_glob(NULL)->line - 1) && (j += (ft_glob(NULL)->maxlen + 1)))
      i = 0;
    if (!begin->dlted)
    {
      print_file(begin);
      put_cursor(i++, j);
    }
    begin = begin->next;
    if (begin->start)
      break;
  }
  put_cursor(ft_glob(NULL)->line + 1, 0);
}

int             main(int argc, char **argv)
{
	char           *name_term;
  struct termios term;
  t_select *info;

  (void)argc;
  handle_winch();
  info = (t_select *)malloc(sizeof(t_select));
  ft_glob(info);
  if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	tgetent(NULL, name_term);

  ft_glob(NULL)->list = ft_parse(argv);
  get_size();
	if (tcgetattr(0, &term) == -1)
		return (-1);
  get_canon(term);
  print_elem(ft_glob(NULL));
  while (1)
    looping();
  set_term(term);
}