/* Startup code, entry point of the kernel launch */

/* Special section in order to get this code in the actual beginning
   of the output binary */
.section ".text.boot"

.globl __start

/* Entrypoint of the actual kernel */
__start:
    /* Setup stack */
    mov sp, #0x8000

    /* Get the start-point and end-point
       of the bss */
    ldr r4, =_bss_start
    ldr r9, =_bss_end

    /* Clear r5-r8 general purpose registers */ 
    eor r5, r5
    eor r6, r6
    eor r7, r7
    eor r8, r8

    /* Begin to clear the bss */
    b 2f
1:
    /* store multiple at r4 */
    stmia r4!, {r5-r8}
2:
    cmp r4, r9  /* Done yet? */
    blo 1b

    /* Call kmain, this is where we "trampoline" to
       the C code... */
#    ldr r3, =kmain
#    blx r3

__stop:
    wfe
    b __stop
