# Práctica 1 #
Existen 5 variables globales para almacenar la configuración del programa:

```c
int invisible = 0;
int normal = 1;
int grueso = 2;
int cfondo = 0;  //Color de fondo
int ctexto = 0;  //Color del texto
```

Las tres primeras variables se usan para determinar el tipo de cursor.

#### gotoxy ####

```c
void goToXY(int x, int y){
    union REGS inregs, outregs;

    inregs.h.ah = 2;
    inregs.h.bh = 0;
    inregs.h.dh = x;     //Posicion x
    inregs.h.dl = y;     //Posicion y
    int86(0x10, &inregs, &outregs);
}
```

#### setcursortype ####

```c
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
      case 2: //Si es grueso
        inregs.h.ch = 000;
        inregs.h.cl = 010;
      break;
    }

    inregs.h.ah = 0x01;
    int86(0x10, &inregs, &outregs);
}
```

#### setvideomode ####


```c
void setVideoMode(unsigned char modo){
   union REGS inregs, outregs;

   inregs.h.ah = 0x00;
   inregs.h.al = modo;
   int86(0x10, &inregs, &outregs);
}
```

#### getvideomode ####

```c
int getVideoMode(){
    union REGS inregs, outregs;

    int86(0x10, &inregs, &outregs);

    return inregs.h.al;
}
```

#### textcolor ####

```c
void textColor(unsigned char color) {
    ctexto = color;
}
```

#### textbackground ####

```c
void textBackground(unsigned char color) {
    cfondo = color;
}
```

#### clrscr ####

```c
int i;
void clrscr() {
    union REGS inregs, outregs;

    int86(0x10, &inregs, &outregs);

    for (i = 0; i < inregs.h.al; i++) {
        printf("\n");
    }

    goToXY(0, 0);
}
```

#### cputchar ####

```c
void cPutChar(unsigned char c) {
    union REGS inregs, outregs;

    inregs.h.ah = 0x09;
    inregs.h.al = c;
    inregs.h.bl = cfondo << 4 | ctexto;
    inregs.h.bh = 0x00;
    inregs.x.cx = 1;

    int86(0x10, &inregs, &outregs);
}
```

#### getche ####

```c
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
```
