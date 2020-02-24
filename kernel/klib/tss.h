/*
 Strayex Kernel C Library "klib"
 v1.1.0
 Kernel Task State Segment file, functions in "tss.c"
 Copyright 2019-2020 Daniel Strayker Nowak
 All rights reserved
*/

#ifndef _TSS_
#define _TSS_

typedef struct tss_entry
{
    unsigned int lastTss;
    unsigned int esp0;
    unsigned int ss0;
    unsigned int esp1;
    unsigned int ss1;
    unsigned int esp2;
    unsigned int ss2;
    unsigned int cr3;
    unsigned int eip;
    unsigned int eflags;
    unsigned int eax;
    unsigned int ecx;
    unsigned int edx;
    unsigned int ebx;
    unsigned int esp;
    unsigned int ebp;
    unsigned int esi;
    unsigned int edi;
    unsigned int es;
    unsigned int cs;
    unsigned int ss;
    unsigned int ds;
    unsigned int fs;
    unsigned int gs;
    unsigned int ldtr;
    unsigned short trap;
    unsigned short iopb;
} __attribute__((packed)) tss_entry_t;

#endif