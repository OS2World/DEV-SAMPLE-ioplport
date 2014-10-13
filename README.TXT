Using INP() and OUTP() under OS/2

The quick synopsys:
******************
1) Compile the supplied example.

2) Do not use inp(), outp(); use iopl_inp() and iopl_outp() in your code.
   The parameters are exactly the same except that the code is 16 bits. (ie
   ints are 2 bytes)

3) Prototype the functions as 
	extern unsigned short __far __pascal iopl_inp(short);
	extern unsigned short __far __pascal iopl_outp(short, short);

4) If you intend to call these functions from a 32-bit application, you
   must put the iopl_inp() and iopl_outp() code in a 16-bit dll.
   


   
The full explanation:
********************
The issues for using INP and OUTP under OS/2 are as follows:

1.inp() and outp() must be recompiled for 16-bits. Use the following code.
 
	unsigned int __far (__pascal or __cdecl) new_inp( int a ) {
		return( _inline_inp( a );
		}
	unsigned int __far (__pascal or __cdecl) new_outp( int a, int b) {
		return( _inline_outp( a, b));
		}

2.The 16-bit code for inp() and outp() should be in its own code segment:
put the following line at the beginning of the file that you want to have
a new code segment.
  #pragma CODE_SEG ("CHOOSE_YOUR_OWN_NAME");
  
3.The linker directive
	SEGMENT code_segment_name IOPL
  must be included where 'code_segment_name' is the name you supplied in the
  pragma in step 2.  In this case it would be 
  	SEGMENT CHOOSE_YOUR_OWN_NAME IOPL

4.The two new functions must be exported (even if they are linked to the
  exe that calls them).  Use the linker directive:
  	EXPORT FUNCTION_NAME #_BYTES_ON_STACK
  where FUNCTION_NAME is the compiler symbol for the function - remember that
  __cdecl retains case and appends the _ suffix; 
  __pascal converts all letters to CAPS and appends nothing.
        #_BYTES_ON_STACK is the number of bytes that will be put on the stack
  to call the given function.  - remember that:
  __cdecl has an algorithm for which arguments must be put on the stack and
  which will be put in registers. Only those bytes put on the stack should
  be considered.
  __pascal puts all arguments on the stack. (this is much easier.)
  
  in the case of step 1. (assume __pascal was used)
  	EXPORT NEW_INP 2, NEW_OUTP 4
	
5.Recompile the new inp/outp file with /s (remove stack overflow checking)
  The __STK function that gets called will try to make a near call to 
  __STK even though it is a far call.  If you need stack checking...you
  can disassemble the compiled file with:
  	wdisasm -l -a file.obj
  and then change the "near" to "far" in the file.lst file at the call to
  __STK.
  Then reassemble with
  	wasm file.lst
	
       
       
There is an example on the BBS called 32C16OS2.ZIP that shows how to call 
a 16-bit DLL from a 32-bit program with various parameters.

Watcom Technical Support
