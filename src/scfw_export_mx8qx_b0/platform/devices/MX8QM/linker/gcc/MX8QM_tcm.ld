/*
** ###################################################################
**     Processors:          MX8
**
**     Compilers:           GNU C Compiler
**
**     Abstract:
**         CMSIS Peripheral Access Layer for MX8
**
**     Copyright (c) 1997 - 2015 Freescale Semiconductor, Inc.
**     Copyright 2016-2021 NXP
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of the copyright holder nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**
** ###################################################################
*/

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

/* Entry Point */
ENTRY(Reset_Handler)

HEAP_SIZE  = DEFINED(__heap_size__)  ? __heap_size__  : 0x1000;
STACK_SIZE = DEFINED(__stack_size__) ? __stack_size__ : 0x1000;
EMUL_SIZE = DEFINED(__emul_size__) ? __emul_size__ : 0x0010;
DEBUG_DATA_SIZE = DEFINED(__debug_data_size__) ? __debug_data_size__ : 0x0040;

/* GUARD_LOG2 defines the power-of-2 size of the MPU guard region
 * used for runtime detection of stack/heap overflow.  Default
 * value is 11 => guard region = 2^11 = 2K
 */
GUARD_LOG2 = DEFINED(__guard_log2__) ? __guard_log2__ : 11;
GUARD_SIZE = (1 << GUARD_LOG2);

/* Specify the memory areas */
MEMORY
{
  m_interrupts          (RX)  : ORIGIN = 0x1ffe0000, LENGTH = 0x00000280
  m_text                (RX)  : ORIGIN = 0x1ffe0280, LENGTH = 0x0002fd70
  m_emul                (RX)  : ORIGIN = 0x2000fff0, LENGTH = 0x00000010
  m_data                (RW)  : ORIGIN = 0x20010000, LENGTH = 0x0000cfc0
  m_debug               (RW)  : ORIGIN = 0x2001cfc0, LENGTH = 0x00000040
  m_data_2              (RW)  : ORIGIN = 0x2001d000, LENGTH = 0x00002800
}

/* Define output sections */
SECTIONS
{ 
  /* The startup code goes first into internal flash */
  .interrupts : 
  {
    . = ALIGN(0x80);
    __VECTOR_TABLE = .;
    KEEP(*(.isr_vector))     /* Startup code */
    . = ALIGN(8);
  } > m_interrupts

  __VECTOR_RAM = __VECTOR_TABLE;
  __RAM_VECTOR_TABLE_SIZE_BYTES = 0x0;

  /* The program code and other data goes into TCM */
  .text : 
  {
    . = ALIGN(8);
    *(.text)                 /* .text sections (code) */
    *(.text*)                /* .text* sections (code) */
    *(.glue_7)               /* glue arm to thumb code */
    *(.glue_7t)              /* glue thumb to arm code */
    *(.eh_frame)
    KEEP (*(.init))
    KEEP (*(.fini))
    . = ALIGN(4);
  } > m_text

  .ARM.extab : 
  {
    *(.ARM.extab* .gnu.linkonce.armextab.*)
  } > m_text

  .ARM : 
  {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } > m_text

 .ctors : 
  {
    __CTOR_LIST__ = .;
    /* gcc uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in.  */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    /* We don't want to include the .ctor section from
       from the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    __CTOR_END__ = .;
  } > m_text

  .dtors : 
  {
    __DTOR_LIST__ = .;
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    __DTOR_END__ = .;
  } > m_text

  .preinit_array : 
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } > m_text

  .init_array : 
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } > m_text

  /* Constants/strings linked to end of image and are allowed to spill over 
     from TCML to TCMU without access penalty (DCODE bus access).  Alignment
     faults must be enabled to ensure an access across the boundary is detected
     not occur */
  .rodata : 
  {
    *(.rodata)               /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)              /* .rodata* sections (constants, strings, etc.) */
  } > m_text

  .fini_array : 
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(64);
  } > m_text

  __etext = .;    /* define a global symbol at end of code */
  __DATA_ROM = .; /* Symbol is used by startup for data initialization */

  .emul :
  {
    __EMUL = .;
    . += EMUL_SIZE;
  } > m_emul

  /* Ensure .data 64-byte aligned for optimized copy */
  .data : AT( LOADADDR(.fini_array) + SIZEOF(.fini_array))
  {
    . = ALIGN(64);
    __DATA_RAM = .;
    __data_start__ = .;      /* create a global symbol at data start */
    *(.data)                 /* .data sections */
    *(.data*)                /* .data* sections */
    KEEP(*(.jcr*))
    . = ALIGN(64);
    __data_end__ = .;        /* define a global symbol at data end */
  } > m_data

  copy_start = LOADADDR(.interrupts);
  copy_end = copy_start;
  copy_dest = copy_start;
  __DATA_END = __DATA_ROM + (__data_end__ - __data_start__);

  /* Uninitialized data section with NO zeroization 
   *
   * Note:  section attribute NOLOAD prevents the linker from allocating space in 
   *        the loadable image (i.e. section type marked NOBITS instead of PROGBITS)
   */
  .noinit (NOLOAD) :
  {
    . = ALIGN(64);
    __NoInitBase = .;
    *(.noinit)
    *(.noinit*)
    . = ALIGN(64);
    __NoInitEnd = .;
  } > m_data

  /* Uninitialized data section */
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */
    . = ALIGN(64);
    __START_BSS = .;
    __bss_start__ = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(64);
    __bss_end__ = .;
    __END_BSS = .;
    __FREE_TCM_START = .;
  } > m_data

  .debug_data :
  {
    __FREE_TCM_END = .;
    __DEBUG_DATA = .;
    . += DEBUG_DATA_SIZE;
  } > m_debug

  .heap :
  {
    . = ALIGN(64);
    __end__ = .;
    PROVIDE(end = .);
    __HeapBase = .;
    . += HEAP_SIZE;
    __HeapLimit = .;
    . = ALIGN(64);
  } > m_data_2

  .guard :
  {
    . = ALIGN(GUARD_SIZE);
    __GuardStart = .;
    . += GUARD_SIZE;
    __GuardLimit = .;
  } > m_data_2

  __GuardSizeMpuField = (GUARD_LOG2 - 1) << 1;

  .stack :
  {
    . = ALIGN(64);
    . += STACK_SIZE;
    . = ALIGN(64);
  } > m_data_2

  /* Initializes stack on the end of block */
  __StackTop   = ORIGIN(m_data_2) + LENGTH(m_data_2);
  __StackLimit = __StackTop - STACK_SIZE;
  PROVIDE(__stack = __StackTop);

  __FREE_TCM_BYTES = __FREE_TCM_END - __FREE_TCM_START;
  __FREE_TCM_WORDS = __FREE_TCM_BYTES >> 2;

  /DISCARD/ : { *(.interp) }
  .ARM.attributes 0 : { *(.ARM.attributes) }

  ASSERT(__StackLimit >= __GuardLimit, "region m_data_2 overflowed with stack and heap")
  ASSERT(__DATA_END < __EMUL, "region m_text overflowed with initialized data")
}

