; Display String
assume cs: code, ds: data
data segment
        str db "Escape the Matrix", "$"; $ is the terminating character
data ends
code segment
         start: MOV AX, data
                MOV DS, AX
                LEA SI, str

                ; DOSBox Interrupt to Displat String having
                ; Starting address stored in DX register
                MOV DX, SI
                MOV AH, 09H
                INT 21H

                MOV AH, 4CH
                INT 21H
code ends
end start