#include <stdio.h>
#include <dos.h>


int invisible = 0;
int normal = 1;
int grueso = 2;
int cfondo = 0;
int ctexto = 0;


//////////////////////////////////////////////////////////////
///////////////////////   goToXY    /////////////////////////
/////////////////////////////////////////////////////////////
void goToXY(int x, int y){
    union REGS inregs, outregs;

    inregs.h.ah = 2;
    inregs.h.bh = 0;
    inregs.h.dh = x;     //Posicion x
    inregs.h.dl = y;     //Posicion y
    int86(0x10, &inregs, &outregs);
}




//////////////////////////////////////////////////////////////
///////////////////////   setCursorType   ///////////////////
/////////////////////////////////////////////////////////////
void setCursorType(int tipo){
    union REGS inregs, outregs;

    switch(tipo){
      case 0: //Si es invisible
        inregs.h.ch = 010;
        inregs.h.cl = 000;
      break;
      case 1: //Si es normal
        inregs.h.ch = 010;
        inregs.h.cl = 010;
      break;
      case 2: //Si es gruedo
        inregs.h.ch = 000;
        inregs.h.cl = 010;
      break;
    }

    inregs.h.ah = 0x01;
    int86(0x10, &inregs, &outregs);
}



//////////////////////////////////////////////////////////////
///////////////////////   setVideoMode  /////////////////////
/////////////////////////////////////////////////////////////
void setVideoMode(unsigned char modo){
   union REGS inregs, outregs;

   inregs.h.ah = 0x00;
   inregs.h.al = modo;
   int86(0x10, &inregs, &outregs);
}



//////////////////////////////////////////////////////////////
///////////////////////   getVideoMode   ////////////////////
/////////////////////////////////////////////////////////////
int getVideoMode(){
    union REGS inregs, outregs;

    int86(0x10, &inregs, &outregs);

    return inregs.h.al;
}



//////////////////////////////////////////////////////////////
///////////////////////   textColor   ///////////////////////
/////////////////////////////////////////////////////////////
void textColor(unsigned char color) {
    ctexto = color;
}



//////////////////////////////////////////////////////////////
///////////////////////   textBackground   //////////////////
/////////////////////////////////////////////////////////////
void textBackground(unsigned char color) {
    cfondo = color;
}



//////////////////////////////////////////////////////////////
///////////////////////   clrscr    /////////////////////////
/////////////////////////////////////////////////////////////
int i;
void clrscr() {
    union REGS inregs, outregs;

    int86(0x10, &inregs, &outregs);

    for (i = 0; i < inregs.h.al; i++) {
        printf("\n");
    }

    goToXY(0, 0);
}



//////////////////////////////////////////////////////////////
///////////////////////   cPutChar   /////////////////////////
/////////////////////////////////////////////////////////////
void cPutChar(unsigned char c) {
    union REGS inregs, outregs;

    inregs.h.ah = 0x09;
    inregs.h.al = c;
    inregs.h.bl = cfondo << 4 | ctexto;
    inregs.h.bh = 0x00;
    inregs.x.cx = 1;

    int86(0x10, &inregs, &outregs);
}



//////////////////////////////////////////////////////////////
///////////////////////   getChe    /////////////////////////
/////////////////////////////////////////////////////////////
void getChe() {
    union REGS inregs, outregs;
    int caracter;

    inregs.h.ah = 1;
    int86(0x21, &inregs, &outregs);
    caracter = outregs.h.al;
    inregs.h.ah = 9;
    inregs.h.al = caracter;

    int86(0x10, &inregs, &outregs);
}



//////////////////////////////////////////////////////////////
///////////////////////   pausa    /////////////////////////
/////////////////////////////////////////////////////////////
void pausa(){
   union REGS inregs, outregs;

   inregs.h.ah = 0x00;
   int86(0x16, &inregs, &outregs);
}


//////////////////////////////////////////////////////////////
///////////////////////   mi_getchar    /////////////////////
/////////////////////////////////////////////////////////////
int mi_getchar(){
  union REGS inregs, outregs;
  int caracter;

  inregs.h.ah = 1;
  int86(0x21, &inregs, &outregs);
  caracter = outregs.h.al;

  return caracter;
}



//////////////////////////////////////////////////////////////
///////////////////////   mi_putchar    /////////////////////
/////////////////////////////////////////////////////////////
void mi_putchar(char c){
  union REGS inregs, outregs;

  inregs.h.ah = 2;
  inregs.h.dl = c;
  int86(0x21, &inregs, &outregs);
}




int main() {
  int tmp;


  //MODO DE VIDEO
  printf("\nInserte modo de video: ");
  tmp = mi_getchar();
  setVideoMode(tmp);
  pausa();


  //OBTENER MODO DE VIDEO
  tmp = getVideoMode();
  printf("\nModo de video: ");
  mi_putchar( (char)tmp );
  pausa();



  //TIPO DE CURSOR
  printf("\nSeleccione tipo de cursor: ");
  tmp = mi_getchar();
  setCursorType(tmp);
  pausa();



  //MOSTRAR CARACTER DE TECLADO EN PANTALLA
  /*printf("\nCaracter para mostrar en pantalla: ");
  getChe();
  pausa();*/



  //MOSTRAR CARACTER CON COLOR
  textColor(1);
  textBackground(2);
  cPutChar('l');
  pausa();



  //BORRAR PANTALLA
  printf("\nSe va a borrar la pantalla");
  pausa();
  clrscr();
  pausa();

  return 0;
}
