DATA SEGMENT
A DB 70H
B DB 60H
C DB 40H
D DB 20H
S DW ?
DATA ENDS
CODE SEGMENT
ASSUME CS:CODE,DS:DATA
START: MOV AX,DATA
MOV DS,AX
MOV AL,A
IMUL B
CWD
MOV BL,C
ADD BL,D
ADC BH,0
IDIV BX
MOV BX,AX
MOV AL,A
CBW
SUB AL,B
SBB AH,0
MOV CL,5
IMUL CL
MOV CL,2
IDIV CL
ADD BX,AX
MOV AL,C
CBW
IDIV D
ADD BL,AL
ADC BH,AH
MOV S,BX
MOV AX,4C00H
INT 21H
CODE ENDS
END START