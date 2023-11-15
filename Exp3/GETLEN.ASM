; Get Length of the String
assume cs: code, ds: data
data segment
        str db "Hello from Jarvis!", "$"
data ends
code segment
         start: MOV AX, data
                MOV DS, AX
                LEA SI, str
                MOV DI, 0200H
                MOV CX, 0000H

           len: MOV AL, [SI]
                CMP AL, "$"
                JZ cont
                INC SI
                INC CX
                JMP len

          cont: MOV [DI], CX
                MOV AH, 4CH
                INT 21H
code ends
end start