        .code32
        .text
        .globl _start
IAT_GetStdHandle = 0x402000
IAT_WriteFile    = 0x402004
IAT_ExitProcess  = 0x402008

_start:
        # Build an EXCEPTION_REGISTRATION_RECORD on the stack and link it at
        # fs:[0], exactly as an MSVC __try prologue does.
        pushl   $handler
        pushl   %fs:0
        movl    %esp, %fs:0

        # Fault: write through a null pointer.
        xorl    %eax, %eax
        movl    $1, (%eax)

resume:
        # Unlink the SEH frame.
        movl    (%esp), %eax
        movl    %eax, %fs:0
        addl    $8, %esp

        pushl   $-11                    # STD_OUTPUT_HANDLE
        call    *IAT_GetStdHandle
        pushl   $0
        pushl   $0x402100               # scratch DWORD in writable .idata
        pushl   $(msgend-msg)
        pushl   $msg
        pushl   %eax
        call    *IAT_WriteFile
        pushl   $0
        call    *IAT_ExitProcess
        hlt

        # EXCEPTION_DISPOSITION __cdecl handler(rec, frame, ctx, dispatch)
handler:
        movl    12(%esp), %eax          # CONTEXT*
        movl    $resume, 0xB8(%eax)     # ctx->Eip = resume
        xorl    %eax, %eax              # ExceptionContinueExecution
        ret

msg:    .ascii  "SEH caught the AV and resumed\n"
msgend:
