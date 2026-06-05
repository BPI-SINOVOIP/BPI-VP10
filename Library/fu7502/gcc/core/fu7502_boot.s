.option norelax

.globl _start
.globl _interrupts
.globl _exception
.globl _ecall
.globl start

.section .vector, "ax"
_interrupts:
    jal     x0, _interrupt_handler_0
    jal     x0, _interrupt_handler_1
    jal     x0, _interrupt_handler_2
    jal     x0, _interrupt_handler_3
    jal     x0, _interrupt_handler_4
    jal     x0, _interrupt_handler_5
    jal     x0, _interrupt_handler_6
    jal     x0, _interrupt_handler_7
    jal     x0, _interrupt_handler_8
    jal     x0, _interrupt_handler_9
    jal     x0, _interrupt_handler_10
    jal     x0, _interrupt_handler_11
    jal     x0, _interrupt_handler_12
    jal     x0, _interrupt_handler_13
    jal     x0, _interrupt_handler_14
    jal     x0, _interrupt_handler_15
    jal     x0, _interrupt_handler_16
    jal     x0, _interrupt_handler_17
    jal     x0, _interrupt_handler_18
    jal     x0, _interrupt_handler_19
    jal     x0, _interrupt_handler_20
    jal     x0, _interrupt_handler_21
    jal     x0, _interrupt_handler_22
    jal     x0, _interrupt_handler_23
    jal     x0, _interrupt_handler_24
    jal     x0, _interrupt_handler_25
    jal     x0, _interrupt_handler_26
    jal     x0, _interrupt_handler_27
    jal     x0, _interrupt_handler_28
    jal     x0, _interrupt_handler_29
    jal     x0, _interrupt_handler_30
    jal     x0, _interrupt_handler_31

_start:
    jal     x0, start

_exception:
    jal     x0, _exception_handler

_ecall:
    jal     x0, _ecall_handler

.section .init

data_init:
    beqz    a0, 1f
0:
    lw      t0, 0(a2)
    sw      t0, 0(a1)
    addi    a0, a0, -4
    addi    a1, a1, 4
    addi    a2, a2, 4
    bnez    a0, 0b
1:
    ret

bss_init:
    beqz    a0, 1f
0:
    sw      zero, 0(a1)
    addi    a0, a0, -4
    addi    a1, a1, 4
    bnez    a0, 0b
1:
    ret

start:
    la      a0, __pram_text_section_size
    la      a1, __pram_text_section_start
    la      a2, __pram_text_initial_values_start
    jal     data_init

    la      a0, __dram_data_section_size
    la      a1, __dram_data_section_start
    la      a2, __dram_data_initial_values_start
    jal     data_init

    la      a0, __dram_bss_section_size
    la      a1, __dram_bss_section_start
    jal     bss_init

    la      sp, __stack_start
    la      gp, __global_pointer$
    jal     main

_endloop:
    j       _endloop

# A default implementation of interrupt handlers that does nothing
_exception_handler:
_ecall_handler:
_interrupt_handler_0:
_interrupt_handler_1:
_interrupt_handler_2:
_interrupt_handler_3:
_interrupt_handler_4:
_interrupt_handler_5:
_interrupt_handler_6:
_interrupt_handler_7:
_interrupt_handler_8:
_interrupt_handler_9:
_interrupt_handler_10:
_interrupt_handler_11:
_interrupt_handler_12:
_interrupt_handler_13:
_interrupt_handler_14:
_interrupt_handler_15:
_interrupt_handler_16:
_interrupt_handler_17:
_interrupt_handler_18:
_interrupt_handler_19:
_interrupt_handler_20:
_interrupt_handler_21:
_interrupt_handler_22:
_interrupt_handler_23:
_interrupt_handler_24:
_interrupt_handler_25:
_interrupt_handler_26:
_interrupt_handler_27:
_interrupt_handler_28:
_interrupt_handler_29:
_interrupt_handler_30:
_interrupt_handler_31:
    mret

.weak _exception_handler
.weak _ecall_handler
.weak _interrupt_handler_0
.weak _interrupt_handler_1
.weak _interrupt_handler_2
.weak _interrupt_handler_3
.weak _interrupt_handler_4
.weak _interrupt_handler_5
.weak _interrupt_handler_6
.weak _interrupt_handler_7
.weak _interrupt_handler_8
.weak _interrupt_handler_9
.weak _interrupt_handler_10
.weak _interrupt_handler_11
.weak _interrupt_handler_12
.weak _interrupt_handler_13
.weak _interrupt_handler_14
.weak _interrupt_handler_15
.weak _interrupt_handler_16
.weak _interrupt_handler_17
.weak _interrupt_handler_18
.weak _interrupt_handler_19
.weak _interrupt_handler_20
.weak _interrupt_handler_21
.weak _interrupt_handler_22
.weak _interrupt_handler_23
.weak _interrupt_handler_24
.weak _interrupt_handler_25
.weak _interrupt_handler_26
.weak _interrupt_handler_27
.weak _interrupt_handler_28
.weak _interrupt_handler_29
.weak _interrupt_handler_30
.weak _interrupt_handler_31
