/* Default linker script, for normal executables */
/*
 * http://www.fortiortech.com
 *
 * Copyright 2023 FortiorTech, Inc.
 *
*/
OUTPUT_FORMAT("elf32-littleriscv", "elf32-littleriscv",
          "elf32-littleriscv")

OUTPUT_ARCH("riscv")
ENTRY(_start)

PROVIDE(__ccfg0 = 0);
PROVIDE(__ccfg1 = 0);
PROVIDE(__ccfg2 = 0);
PROVIDE(__ccfg3 = 0);
INPUT(rv_cfg)

MEMORY
{
    ROM   (RX)  : ORIGIN = 0x00000000, LENGTH = 64k-16
    CFG   (R)   : ORIGIN = 0x0000fff0, LENGTH = 16
    PRAM  (RWX) : ORIGIN = 0x10000000, LENGTH = 4k
    DRAM  (RW)  : ORIGIN = 0x20000000, LENGTH = 12k-568
}

SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        *(.vector)
        *(.init)
        *(SORT_BY_ALIGNMENT(.text*))
        *(SORT_BY_ALIGNMENT(.srodata*))
        *(SORT_BY_ALIGNMENT(.rodata*))
        . = ALIGN(4);
    } >ROM AT>ROM

    __dram_data_initial_values_start = .;
    .data : AT(__dram_data_initial_values_start)
    {
        . = ALIGN(4);
        __dram_data_section_start = .;

        *(SORT_BY_ALIGNMENT(.sdata*))
        *(SORT_BY_ALIGNMENT(.data*))
        *(SORT_BY_ALIGNMENT(.got*))
        *(SORT_BY_ALIGNMENT(.rela*))

        . = ALIGN(4);
    } >DRAM
    __dram_data_section_size = SIZEOF(.data);

    .bss :
    {
        . = ALIGN(4);
        __dram_bss_section_start = .;

        *(SORT_BY_ALIGNMENT(.sbss*))
        *(SORT_BY_ALIGNMENT(.bss*))
        *(SORT_BY_ALIGNMENT(COMMON))

        . = ALIGN(4);
    } >DRAM AT>DRAM
    __dram_bss_section_size  = SIZEOF(.bss);

    __global_pointer$ = __dram_bss_section_start;

    .stack :
    {
        . = ALIGN(4);
        PROVIDE(__stack_end = .);
    } >DRAM AT>DRAM
    __stack_start = ORIGIN(DRAM) + LENGTH(DRAM);
    __stack_size = __stack_start - __stack_end;

    __pram_text_initial_values_start = __dram_data_initial_values_start + __dram_data_section_size;
    .ptext : AT(__pram_text_initial_values_start)
    {
        . = ALIGN(4);
        __pram_text_section_start = .;

        *(SORT_BY_ALIGNMENT(.pram.text*))
		*(SORT_BY_ALIGNMENT(.pram.data*))
        . = ALIGN(4);
    } >PRAM
    __pram_text_section_size = SIZEOF(.ptext);

    .cfg :
    {
        LONG(__ccfg3)
        LONG(__ccfg2)
        LONG(__ccfg1)
        LONG(__ccfg0)
    } >CFG AT>CFG

    /DISCARD/ :
    {
        *(.eh_frame_hdr)
        *(.gcc_except_table)
        *(.jcr)
    }
}

ASSERT(__stack_start >= __stack_end, "Error: Stack size is negative or zero!");
ASSERT((__dram_bss_section_start + __dram_bss_section_size) <= __stack_start,
       "Error: .bss section overlaps with stack space!");
