section .data
    ; On définit les variables ici si nécessaire

section .text
    global _start       ; Point d'entrée pour l'éditeur de liens (ld)

_start:
    mov eax, 8          ; Met la valeur 8 dans le registre EAX
    
    ; Pour afficher ou tester, nous allons simplement 
    ; quitter le programme en retournant le code 8.
    mov ebx, eax        ; EBX contient le code de retour (8)
    mov eax, 1          ; Code de l'appel système 'sys_exit'
    int 0x90            ; Interruption logicielle pour appeler le noyau
  
    
