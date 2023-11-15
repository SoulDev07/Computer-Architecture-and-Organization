assume cs: code, ds: data
data segment
data ends
code segment
         start: MOV AX, data
                MOV DS, AX
                MOV SI, 0100H
                MOV DI, 0200H
                MOV CX, 0000H

                MOV AX, [SI]
                ADD AX, [SI + 2]
                MOV [DI], AX
                JNC nocarry
                INC CX

       nocarry: MOV [DI + 2], CX
                MOV AH, 4CH
                INT 21H
code ends
end start