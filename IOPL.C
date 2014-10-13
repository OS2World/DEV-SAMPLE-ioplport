#pragma CODE_SEG ( "MY_CODE" );

unsigned int __far __pascal iopl_inp(int a) {
    return (_inline_inp(a));
}

unsigned int __far __pascal iopl_outp(int a, int b) {
    return (_inline_outp(a, b));
}
