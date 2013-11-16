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

/* To communicate with the GPU mailbox */
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

#endif
