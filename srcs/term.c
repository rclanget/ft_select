#include "ft_select.h"

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

  clearstr = tgetstr("cl", &ap);
  tputs(clearstr, 1, ft_putch);
}

void get_size(void)
{
  struct winsize w;

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  ft_glob(NULL)->col = w.ws_col;
  ft_glob(NULL)->line = w.ws_row;
}
