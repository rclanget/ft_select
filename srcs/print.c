#include "ft_select.h"
#include "libft.h"

int ft_exit(void)
{
  set_term(ft_glob(NULL)->sauv);
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
  char *standout;
  char *stendout;

  standout = tgetstr("so", NULL);
  stendout = tgetstr("se", NULL);
  ft_putstr_fd(standout, ft_glob(NULL)->out_fd);
  ft_putstr_fd(str, ft_glob(NULL)->out_fd);
  ft_putstr_fd(stendout, ft_glob(NULL)->out_fd);
}

void print_underline(char *str)
{
  char *standout;
  char *stendout;

  standout = tgetstr("us", NULL);
  stendout = tgetstr("ue", NULL);
  ft_putstr_fd(standout, ft_glob(NULL)->out_fd);
  ft_putstr_fd(str, ft_glob(NULL)->out_fd);
  ft_putstr_fd(stendout, ft_glob(NULL)->out_fd);
}

void print_underline_video(char *str)
{
  char *standout_v;
  char *stendout_v;
  char *standout;
  char *stendout;

  standout = tgetstr("us", NULL);
  stendout = tgetstr("ue", NULL);
  standout_v = tgetstr("so", NULL);
  stendout_v = tgetstr("se", NULL);
  ft_putstr_fd(standout, ft_glob(NULL)->out_fd);
  ft_putstr_fd(standout_v, ft_glob(NULL)->out_fd);
  ft_putstr_fd(str, ft_glob(NULL)->out_fd);
  ft_putstr_fd(stendout, ft_glob(NULL)->out_fd);
  ft_putstr_fd(stendout_v, ft_glob(NULL)->out_fd);
}

int print_file(t_lst *lst)
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
  return (1);
}

void put_cursor(int i, int j)
{
  char *gotostr;

  gotostr = tgetstr("cm", NULL);
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
    if (!begin->dlted && print_file(begin))
      put_cursor(i++, j);
    if ((j + ft_glob(NULL)->maxlen) > ft_glob(NULL)->col)
      break;
    begin = begin->next;
    if (begin->start)
      break;
  }
  current ? put_cursor(ft_glob(NULL)->line + 1, 0) : print_elem(begin->next);
}
