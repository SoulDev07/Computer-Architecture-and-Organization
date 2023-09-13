; Generalized Version of Copy & Paste
; No of element is 8, Size of element is 8
assume cs: code, ds: data
data segment
        counter dw 0008H
data ends
code segment
         start: MOV AX, data
                MOV DS, AX
                MOV SI, 0105H
                MOV DI, 0100H
                MOV CX, counter

	        CMP SI, DI
	        JNC ncarry; Transfer data in normal fashion if SI > DI
                ADD SI, CX
                DEC SI
                ADD DI, CX
                DEC DI

	 carry: MOV AL, [SI]
                MOV [DI], AL
                DEC SI
                DEC DI
                DEC CL
	        JNZ carry
	        JMP exit

        ncarry: MOV AL, [SI]
                MOV [DI], AL
                INC SI
                INC DI
                DEC CL
	        JNZ ncarry

          exit: MOV AH, 4CH
                INT 21H
code ends
end start