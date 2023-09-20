; Transfer String from one memory location to another
assume cs: code, ds: data, es: extra
data segment
        str1 db "Hello World!", "$"
        counter dw 000CH
data ends

extra segment
        str2 db 12 dup(0), "$"; Size is in Decimal
extra ends

code segment
         start: MOV AX, data
                MOV DS, AX

                MOV AX, extra
                MOV ES, AX

                LEA SI, str1
                LEA DI, str2
                CLD; Clear Direction Flag

                MOV CX, counter

        ;   UP: MOVSB
        ;       LOOP UP
        ; Loops till Value in CX is not Zero

                REP MOVSB; Repeat MOVSB CX Times, REP is Prefix

                LEA DX, str2
                MOV AH, 09H
                INT 21H
                         
                MOV AH, 4CH
                INT 21H
code ends
end start
