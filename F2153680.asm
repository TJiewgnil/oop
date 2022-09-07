MYDATA SEGMENT
DATA DW 1234H,5678H,9D4CH,0D7H,0,-1,7D2AH,8A0EH,10F5H,645DH
N EQU $-DATA
MYDATA ENDS

CODE SEGMENT
ASSUME DS:MYDATA,CS:CODE
MAIN PROC FAR
START:MOV AX,MYDATA
MOV DS,AX

LEA SI,DATA
MOV CX,N-1
MOV AX,[SI]
ADD SI,2

EVENNUM:TEST BYTE PTR [SI],1
JNZ NEXT

COMP:CMP AX,[SI]
JG NEXT
MOV AX,[SI]

NEXT:ADD SI,2
LOOP EVENNUM

TEST AX,1
JNZ EXIT
MOV BX,AX
CALL TRANS
RET
EXIT:
MAIN ENDP

TRANS PROC NEAR
PUSH BX
MOV AX,BX
MOV BX,1000H
MOV CL,4

OUTPUT:
CWD
DIV BX
PUSH DX
MOV DL,AL
CMP DL,10
JB PRINT
ADD DL,-10+'A'-'0'

PRINT:ADD DL,'0'
MOV AH,2
INT 21H

SHR BX,CL
POP DX
MOV AX,DX
CMP BX,0
JG OUTPUT

POP BX
RET
TRANS ENDP
CODE ENDS
END MAIN