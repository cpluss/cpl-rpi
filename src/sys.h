#ifndef SYS_H
#define SYS_H

#include "types.h"

/* Bus location base address */
#define ARM_BUS_LOCATION    (uint)0x40000000

/* GPIO (General Purpose Input Output) address */
#define ARM_GPIO_BASE_ADDR  (uint)0x20200000

/* Peripheral (usb) base address */
#define ARM_PERIPHERAL_BASE (uint)0x20000000
#define ARM_COUNTER_ADDR    (uint)0x20003004

/* To communicate with the rpi mailbox 
    This is hardware based communication and can happen
    through numereous channels:
        * 0 - Power management interface
        * 1 - Framebuffer (GPU)
        * 2 - Virtual UART
        * 3 - VCHIQ Interface (no idea what this is)
        * 4 - LEDs interface
        * 5 - Buttons interface
        * 6 - Touch screen interface
 */
#define ARM_MAIL_BASE       (uint)0x2000B880
/* Mailbox can either be empty or full */
#define MAIL_FULL           0x80000000
#define MAIL_EMPTY          0x40000000
/* We can read, write, or check the status of the mailbox */
#define ARM_MAIL_READ       0x00
#define ARM_MAIL_WRITE      0x20
#define ARM_MAIL_STATUS     0x18

#define KERNEL_FB_LOC (volatile uint)0x00002000

/*
 The rpi requires you to translate requests between _bus_ and _physical_
 locations in memory
 */
volatile uint phys_to_bus(uint p);
volatile uint bus_to_phys(uint p);

/* 
 In order for some hardware communications to work properly
 you have to sync/clear certain memory locations (called barrier). */
void mem_barrier();

/*
 Mailbox functions, in order to write/read to a 
 specific channel. */
void MailboxWrite(char channel, uint data);
uint MailboxRead(char channel);
/* 
 Read mailbox status */
uint MailboxStatus();

/* GPU Framebuffer structure */
typedef struct gpu {
    /* Requested width and height */
    uint width, height; 

    /* Virtual width and height, better set it zero */
    uint virtual_width,virtual_height;

    /* Number of bytes between each row of the frame buffer,
       returned by the GPU */
    uint pitch;

    /* The number of bits per pixel of the requested frame buffer, 
       Linux seems to use 16bit, but we set default 24 */
    uint depth;

    /* Offsets in both y- and x-directions */
    uint x_offset, y_offset;

    /* Pointer to the frame buffer, returned by the GPU */
    uint pointer;

    /* Actual size of the frame buffer */
    uint size;
} gpu_t;

#endif
