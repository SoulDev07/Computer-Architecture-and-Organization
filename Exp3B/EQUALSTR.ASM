assume cs: code, ds: data, es: extra
data segment
        str1 db "String Test", "$"
        counter dw 1011H
        eqs db "String is Equal!", "$"
        noteq db "String is not Equal!", "$"
data ends
extra segment
        str2 db "String Test", "$"
extra ends
code segment
         start: MOV AX, data
                MOV DS, AX
                MOV AX, extra
                MOV ES, AX
                MOV CX, counter
                LEA SI, str1
                LEA DI, str2
                CLD

                REPE CMPSB
                JNZ notEqual
                LEA DX, eqs
                JMP exit

      notEqual: LEA DX, noteq
          exit: MOV AH, 09H
                INT 21H
                MOV AH, 4CH
                INT 21H
code ends
end start