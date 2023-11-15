; No of element is 16, Size of element is 8, SI = 100, DI = 200
assume cs: code, ds: data
data segment
        counter dw 0010H
data ends
code segment
                ; Initialization
         start: MOV AX, data
                MOV DS, AX
                MOV SI, 0100H
                MOV DI, 0200H
                MOV CX, counter

                ; Transfer 8-bit data from SI to DI CX Times
          jump: MOV AL, [SI]; AX is not used as [SI] and [SI + 1] will get transferred
                MOV [DI], AL
                INC SI
                INC DI
                DEC CX
                JNZ jump

                ; Terminate (DOSBox Interrupt to End Program)
                MOV AH, 4CH
                INT 21H
code ends
end start