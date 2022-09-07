DATA SEGMENT
NOO DB 5
CHAR DB 81,?,81 DUP(?)
CZ DB 81 DUP(0)
NZ DB 81 DUP(0)
IM DB 'PLEASE ENTER A STRING OF CHARACTERS(NO MORE THAN 80)',0AH,0DH,'$'
OM DB 0AH,0DH,'CHARACTER QUANTITY FREQUENCY',0AH,0DH,'$'
enter db 0ah,0dh,'$'
space db '      $'
full db '100%$'
DATA ENDS

CODE SEGMENT
ASSUME DS:DATA,CS:CODE
MAIN:MOV AX,DATA
MOV DS,AX
CALL INPUT
CALL STATISTIC
CALL OUTPUT
MOV AX,4C00H
INT 21H

INPUT PROC NEAR
LEA DX,IM
MOV AH,09H
INT 21H
LEA DX,CHAR
MOV AH,0AH
INT 21H
RET
INPUT ENDP

STATISTIC PROC NEAR
MOV CL,CHAR+1
MOV CH,0
PUSH CX
MOV AH,'z'
MOV AL,'a'
LEA BX,CHAR+2-1
CASE:
INC BX
CMP [BX],AL
JL DONE
CMP [BX],AH
JG DONE
MOV DL,'A'-'a'
ADD [BX],DL
DONE:
LOOP CASE

POP CX
LEA BX,CHAR+2

THROUGH:
LEA DI,CZ
LEA SI,NZ
PUSH CX
MOV AL,[BX]

DIF:
CMP [DI],CH
JZ INSERT
CMP AL,[DI]
JZ PLUS
INC DI
CMP [DI],CH
JNZ DIF

INSERT:
MOV [DI],AL

PLUS:
LEA AX,CZ
SUB DI,AX
ADD SI,DI
MOV AL,1
ADD [SI],AL

POP CX
INC BX
LOOP THROUGH

ret
statistic endp

OUTPUT proc near
LEA DX,OM
MOV AH,09H
INT 21H

mov al,0
mov cl,noo
lea bx,nz-1
output_bit:
inc bx
cmp [bx],al
jz output_bit_lf
loop output_bit
output_bit_lf:
mov al,noo
sub al,cl
mov cl,al

sort:
push cx
lea si,nz
lea bx,nz
biggest:
inc si
mov al,[si]
cmp al,0
jz print
cmp al,[bx]
jng biggest
mov bx,si
loop biggest

print:
lea dx,space
mov ah,9
int 21h
mov cl,[bx]
mov si,bx
lea ax,nz
sub bx,ax
lea ax,cz
add bx,ax
mov dl,[bx]
mov dh,0
mov ah,2
int 21h
lea dx,space
mov ah,9
int 21h

mov ch,cl
mov al,9
cmp cl,al
jng bit

mov al,cl
cbw
mov dl,10
div dl
mov dl,al
add dl,'0'
mov ah,2
int 21h
mov cl,ah

bit:
mov dl,cl
add dl,'0'
mov ah,2
int 21h
lea dx,space
mov ah,9
int 21h

call frequency

mov al,[si]
mov dl,-1
mov [si],dl

pop cx
cmp cx,1
jnz statistic_end
call jux

statistic_end:
loop sort
ret
output endp

frequency proc near
mov cl,ch
mov ch,0
mov bl,char+1
cmp bl,cl
jnz normal
lea dx,full
mov ah,9
int 21h
lea dx,enter
mov ah,9
int 21h
jmp frequency_end

normal:
mov ax,cx
mov bx,10000
mul bx
mov bl,char+1
mov bh,0
div bx
mov bx,10000
mov cl,4
mov ch,0


percentage:
cwd
div bx
push dx
cmp cl,2
jng output_per
cmp ax,0
jz next_space

output_per:
cmp cl,1
jnz number
cmp dx,5
jl point
inc ax

point:
push ax
mov dl,'.'
mov ah,2
int 21h
pop ax

number:
mov dl,al
add dl,'0'
mov ah,2
int 21h
jmp next

next_space:
mov dl,' '
mov ah,2
int 21h

next:
mov ax,bx
cwd
mov bx,10
div bx
mov bx,ax
pop dx
mov ax,dx
loop percentage

mov dl,'%'
mov ah,2
int 21h
lea dx,enter
mov ah,9
int 21h

frequency_end:
ret
frequency endp

jux proc near
mov ah,0
lea bx,nz
leastf_jux:
inc bx
cmp [bx],ah
jz jux_end
cmp al,[bx]
jnz leastf_jux
inc cl
jmp leastf_jux

jux_end:
ret
jux endp

code ends
end main