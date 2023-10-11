assume cs: code, ds: data
data segment
        str db "edbca", "$"
data ends
code segment
         start: MOV AX, data
                MOV DS, AX
                MOV CX, 0000H
                CLD

           len: MOV AL, [SI]
                CMP AL, "$"
                JZ cont
                INC SI
                INC CX
                JMP len

          cont: DEC CX
         outer: LEA SI, str
                MOV DX, 0000H

         inner: MOV AX, [SI]
                CMP AH, AL
                JNC noSwap
                XCHG AH, AL
                MOV [SI], AX

        noSwap: INC SI
                INC DX
                CMP DX, CX
                JC inner
                DEC CX
                JNZ outer

                LEA DX, str
                MOV AH, 09H
                INT 21H
                MOV AH, 4CH
                INT 21H
code ends
end start