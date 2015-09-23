#include "ft_select.h"
#include "libft.h"
#include <sys/ioctl.h>

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

void clear_win(void)
{
  char buf[30];
  char *ap = buf;
  char *clearstr;
  int  line;

  line = ft_glob(NULL)->line;
  clearstr = tgetstr("dl", &ap);
  while (line-- >= 0)
  {
    ft_putstr_fd(clearstr, ft_glob(NULL)->out_fd);
    put_cursor(line, 0);
  }
}

void stat_cursor(int stat)
{
  char buf[30];
  char *ap = buf;
  char *cursor;

  cursor = tgetstr(stat ? "ve" : "vi", &ap);
  ft_putstr_fd(cursor, ft_glob(NULL)->out_fd);
}

void get_size(void)
{
  struct winsize w;

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  ft_glob(NULL)->col = w.ws_col;
  ft_glob(NULL)->line = w.ws_row;
}
