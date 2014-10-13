#include <conio.h>

extern unsigned int __far __pascal iopl_inp(int);
extern unsigned int __far __pascal iopl_outp(int, int);

void main()
  {
    iopl_outp( 0x61, iopl_inp(0x61 ) & 0xFC);
  }
