; Check if String is Palidrome
assume cs: code, ds: data
data segment
        str db "racecar", "$"
        pal db "Is Palindrome", "$"
        npal db "Is not Palindrome", "$"
data ends
code segment
         start: MOV AX, data
                MOV DS, AX
                MOV CX, 0000H
                LEA SI, str
                LEA DI, str

           len: MOV AL, [SI]
                CMP AL, "$"
                JZ cont
                INC SI
                INC CX
                JMP len

          cont: LEA SI, str
                ADD DI, CX
                DEC DI
                SHR CX, 1

        repeat: MOV AL, [SI]
                MOV BL, [DI]
                INC SI
                DEC DI
                CMP AL, BL
                JNZ notPalindrome
                DEC CX
                JNZ repeat
                LEA DX, pal
                JMP exit

 notPalindrome: LEA DX, npal

          exit: MOV AH, 09H
                INT 21H
                MOV AH, 4CH
                INT 21H
code ends
end start