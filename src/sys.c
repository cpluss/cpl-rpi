#include "sys.h"

/*
 The rpi requires you to translate requests between _bus_ and _physical_
 locations in memory
 */
volatile uint phys_to_bus(uint p) {
    return (uint)(p + ARM_BUS_LOCATION);
}

volatile uint bus_to_phys(uint p) {
    if(p > ARM_BUS_LOCATION) {
        return (uint)(p - ARM_BUS_LOCATION);
    }
    return (uint)p;
}

/*
 Put up a memory "barrier" in order to properly function with some
 of the hardware */
void mem_barrier() {
    asm volatile("mcr p15, 0, ip, c7, c5, 0");
    asm volatile("mcr p15, 0, ip, c7, c5, 6");
    asm volatile("mcr p15, 0, ip, c7, c5, 4");
    asm volatile("mcr p15, 0, ip, c7, c5, 4");
}

/* 
 Return the mailbox status */
uint MailboxStatus() {
    volatile uint *p = (volatile uint*)(ARM_MAIL_BASE + ARM_MAIL_STATUS);
    return (uint)(*p);
}

/*
 Write 'data' to the mailbox on a specific channel */
void MailboxWrite(char channel, uint data) {
    // We can not write if the mailbox is full
    while(MailboxStatus() & MAIL_FULL);

    mem_barrier();
    *(volatile uint*)(ARM_MAIL_BASE + ARM_MAIL_WRITE) = channel | (data & 0xFFFFFFF0);
    mem_barrier();
}

/*
 Read data from the mailbox in a specific channel */
uint MailboxRead(char channel) {
    uint ret = 0, i;
    for(i = 0;;) {
        // Can not read from an empty mailbox now, can we?
        while(MailboxStatus() & MAIL_EMPTY) {
            if(++i >= (1 << 20)) {
                //TODO: Add properly error handling
                return 0xFFFFFFFF;
            }
        }

        mem_barrier();
        ret = *(volatile uint*)(ARM_MAIL_BASE);
        mem_barrier();

        // Check if it's the correct channel
        if((ret & 0x0000000F) == channel) {
            break;
        }
    }

    /* Note how we strip of the last 4 bits, which actually
       is the channel */
    return (ret & 0xFFFFFFF0);
}
