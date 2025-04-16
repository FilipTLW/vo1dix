MBALIGN     equ   1 << 0                            ; multiboot constants
MEMINFO     equ   1 << 1
VMTINFO     equ   1 << 2
MBFLAGS     equ   MBALIGN | MEMINFO | VMTINFO
MAGIC       equ   0x1BADB002
CHECKSUM    equ   -(MAGIC + MBFLAGS)
GRAPH_MODE  equ   0

section .multiboot                                  ; multiboot header, will be at the beginning of the binary
align 4
  dd MAGIC
  dd MBFLAGS
  dd CHECKSUM
  dd 0                                              ; header_addr non relevant
  dd 0                                              ; load_addr non relevant
  dd 0                                              ; load_end_addr non relevant
  dd 0                                              ; bss_end_addr non relevant
  dd 0                                              ; entry_addr non relevant
  dd GRAPH_MODE                                     ; mode_type set to linear graphics mode
  dd 320
  dd 200
  dd 8

section .bss                                        ; uninitialized data (read-write)
align 16
stack_bottom:
resb 16384                                          ; reserve 16 KiB for the stack
stack_top:                                          ; this is the "beginning" of the stack, as the stack grows downwards

section .text                                       ; entrypoint will be put right after multiboot header in the binary

global _start:function (_start.end - _start)        ; Export _start as a function

_start:
  mov esp, stack_top                                ; initialize stack pointer to the beginning of the stack
                                                    ; because the stack grows downwards it has to be the
                                                    ; top of the stack
  push ebx
  extern _init
  call _init

  extern kernel_main
  call kernel_main                                  ; continue execution in kernel.c

  cli                                               ; prevent any further interrupts
.hang:
  jmp .hang                                         ; infinite loop
.end: