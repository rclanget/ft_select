#include "ft_select.h"
#include "libft.h"
#include <sys/ioctl.h>

#include "ft_printf.h"

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
  int  line;

  line = GET(line);
  while (line-- >= 0)
  {
    PUT("dl");
    put_cursor(line, 0);
  }
}

void stat_cursor(int stat)
{
  PUT(stat ? "ve" : "vi");
}

void get_size(void)
{
  struct winsize w;

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  SET(col, w.ws_col);
  SET(line, w.ws_row);
}
