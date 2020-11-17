# 1 "D:\\IGOR\\STUDY\\stm32f407_mpt_lab\\SEGGER_THUMB_Startup.s"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "D:\\IGOR\\STUDY\\stm32f407_mpt_lab\\SEGGER_THUMB_Startup.s"
# 60 "D:\\IGOR\\STUDY\\stm32f407_mpt_lab\\SEGGER_THUMB_Startup.s"
        .syntax unified
# 83 "D:\\IGOR\\STUDY\\stm32f407_mpt_lab\\SEGGER_THUMB_Startup.s"
        .extern main
# 111 "D:\\IGOR\\STUDY\\stm32f407_mpt_lab\\SEGGER_THUMB_Startup.s"
        .section .init, "ax"
        .balign 2
        .global _start
        .thumb_func
        .code 16
_start:






        ldr R4, =__SEGGER_init_table__
__SEGGER_init_run_loop:
        ldr R0, [R4]
        adds R4, R4, #4
        blx R0
        b.n __SEGGER_init_run_loop

       .thumb_func
       .global __SEGGER_init_done
__SEGGER_init_done:
# 142 "D:\\IGOR\\STUDY\\stm32f407_mpt_lab\\SEGGER_THUMB_Startup.s"
        bl main



        .global exit
        .thumb_func
exit:




        b .
