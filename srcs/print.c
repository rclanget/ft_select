#include "ft_select.h"
#include "libft.h"

int             voir_touche()
{
  char     buffer[3];
 
  while (1)
  {
    read(0, buffer, 3);
    if (buffer[0] == 27)
    {
      printf("Ctlr+d, on quitte !\n");
      return (0);
    }
  }
  return (0);
}

void set_term(struct termios term)
{
  tcsetattr(0, TCSADRAIN, &term);  
}

void  get_canon(struct termios term)
{
  term.c_lflag &= ~(ICANON); // Met le terminal en mode canonique.
  term.c_lflag &= ~(ECHO); // les touches tapées ne s'inscriront plus dans le terminal
  term.c_cc[VMIN] = 1;
  term.c_cc[VTIME] = 0;
  set_term(term);
}

int ft_putch(int c)
{
  return (write(1, &c, 1));
}
    
void print_elem(t_list *elem)
{

  char buf[30];
  char *ap = buf;
  char *gotostr;
  int i;
  int j;

  i = 1;
  j = 0;
  elem = elem->next;
  gotostr = tgetstr("cm", &ap);
  while (!elem->start)
  {
    if (i++ == ft_glob(NULL)->line - 1)
    {
      j += ft_glob(NULL)->maxlen + 1;
      i = 0;
    }
    tputs(elem->file, 1, ft_putch);
    tputs(tgoto(gotostr, j, i), 1, ft_putch);
    elem = elem->next;
  }
  tputs(tgoto(gotostr, 0, ft_glob(NULL)->line + 1), 1, ft_putch);
}

void clear_win(void)
{
  char buf[30];
  char *ap = buf;
  char *clearstr;

  clearstr = tgetstr("cl", &ap);
  tputs(clearstr, 1, ft_putch);
}

void get_size(void)
{
  ft_glob(NULL)->col = tgetnum("co");
  ft_glob(NULL)->line = tgetnum("li");
}

int             main(int argc, char **argv)
{
	char           *name_term;
  struct termios term;
  t_select *info;

  (void)argc;
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
  clear_win();
  print_elem(ft_glob(NULL)->list);
  set_term(term);
  sleep(5);
  tputs("\n", 1, ft_putch);
}