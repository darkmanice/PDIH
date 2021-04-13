#include <ncurses.h>
#include <unistd.h>


#define DELAY 150000

int main(int argc, char const *argv[]) {
  int x, y;
  int max_y, max_x;
  int next_x = 0;
  int directionx = 1;
  int next_y = 0;
  int directiony = 1;
  int height = 0, width = 0;
  int points_sup = 0, points_inf = 0;

  int xcs, ycs;
  int xci, yci;
  int ch = 0;

  initscr();
  noecho();
  cbreak();
  curs_set(FALSE);
  nodelay(stdscr, TRUE);

  getmaxyx(stdscr, height, width);
  x = width/2;
  y = height-4;
  max_y = height - 1;
  max_x = width;
  yci = height - 2;
  xci = width/2 - 5;  //LA BARRA TIENE TAMAÑO 10, PARA CENTRARLA RESTAMOS 5
  ycs = 1;
  xcs = width/2 - 5;   //LA BARRA TIENE TAMAÑO 10, PARA CENTRARLA RESTAMOS 5

  while(1){
    clear();
    mvprintw(y, x, "o");
    mvprintw(0, 0,"Puntos: %d", points_sup);
    mvprintw(height - 1, 0, "Puntos: %d %d %d", points_inf, yci, height);
    mvprintw(ycs, xcs, "NNNNNNNNNNN");
    mvprintw(yci, xci, "NNNNNNNNNNN");
    refresh();

    ch = getch();

    if(ch == 'a' && xcs > 0)
      xcs -= 6;
    else if(ch == 'd' && xcs + 15  < width)
      xcs += 6;

    if(ch == 'k' && xci > 0)
      xci -= 6;
    else if(ch == 'l' && xci + 15 < width)
      xci += 6;

    usleep(DELAY);

    next_x = x + directionx;
    next_y = y + directiony;

    if(next_x >= max_x || next_x < 0)
      directionx *= -1;
    else
      x += directionx;

    if(next_y >= max_y || next_y < 0)
      directiony *= -1;
    else
      y += directiony;

    //SI REBOTA EN LA BARRA INFERIOR
    if(x >= xci && x <= xci + 10 && y == height - 3){
      directionx *= -1;
      directiony *= -1;
    } else
      x += directionx;

    //SI REBOTA EN LA BARRA SUPERIOR
    if(x >= xcs && x <= xcs + 10 && y == 3){
      directionx *= -1;
      directiony *= -1;
    } else
      x += directionx;

    //SISTEMA DE PUNTUACION
    if(y < 1){
      points_inf += 1;
      getmaxyx(stdscr, height, width);
      x = width/2;
      y = height/2;
      max_y = height - 1;
      max_x = width;
      yci = height - 2;
      xci = width/2 - 5;  //LA BARRA TIENE TAMAÑO 10, PARA CENTRARLA RESTAMOS 5
      ycs = 1;
      xcs = width/2 - 5;  //LA BARRA TIENE TAMAÑO 10, PARA CENTRARLA RESTAMOS 5

      mvprintw(y, x, "o");
      mvprintw(ycs, xcs, "NNNNNNNNNNN");
      mvprintw(yci, xci, "NNNNNNNNNNN");
    } else if(y >= height - 2){
      points_sup += 1;
      getmaxyx(stdscr, height, width);
      x = width/2;
      y = height/2;
      max_y = height - 1;
      max_x = width;
      yci = height - 2;
      xci = width/2 - 5;  //LA BARRA TIENE TAMAÑO 10, PARA CENTRARLA RESTAMOS 5
      ycs = 1;
      xcs = width/2 - 5;  //LA BARRA TIENE TAMAÑO 10, PARA CENTRARLA RESTAMOS 5

      mvprintw(y, x, "o");
      mvprintw(ycs, xcs, "NNNNNNNNNNN");
      mvprintw(yci, xci, "NNNNNNNNNNN");
    }
  }

  endwin();

  return 0;
}
