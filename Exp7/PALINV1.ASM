; Check if String is Palidrome
assume cs: code, ds: data, es: extra
data segment
        str1 db "racecar", "$"
        counter dw 0007H
        pal db "Is Palindrome", "$"
        npal db "Is not Palindrome", "$"
data ends
extra segment
        str2 db 7 dup(0), "$"
extra ends
code segment
         start: MOV AX, data
                MOV DS, AX
                MOV AX, extra
                MOV ES, AX

                LEA SI, str1
                LEA DI, str2
                MOV CX, counter
                ADD DI, CX
                DEC DI

        repeat: CLD
                LODSB
                STD
                STOSB
                LOOP repeat

                LEA SI, str1
                LEA DI, str2
                MOV CX, counter
                CLD

                REPE CMPSB
                JNZ notEqual
                LEA DX, pal
                JMP exit

      notEqual: LEA DX, npal
          exit: MOV AH, 09H
                INT 21H
                MOV AH, 4CH
                INT 21H
code ends
end start