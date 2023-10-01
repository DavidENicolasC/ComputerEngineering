COMMENT * Escribir un programa que saque en pantalla con el formato
          Mi nombre es david
          utilizando el ciclo jcxz y la instruccion jmp
          con directivas no simplificadas. *
        
pila segment para stack 'stack'                    ;Se define el area de la pila
     db 64 dup(0)                                  ;Reserva 64 bytes inicializando todos con el valor 0
pila ends                                          ;Fin del segmento

datos segment para 'data'                          ;Se define el area de los datos
mensaje db 'Mi nombre es david', 07, 13, 10, '$'   ;Se define la variable mensaje
datos ends                                         ;Fin del segmento

codigo segment para 'code'                         ;Se define el area de codigo
       assume cs:codigo, ds:datos, ss:pila         ;Indica al ensamblador como direccionar la informacion
inicio proc far                                    ;Inicio del procedimiento

        mov ax, datos                               ;Asigna la dirección del segmento de datos a AX y
        mov ds, ax                                  ;a través de AX asigna la dirección de datos a DS

        mov cx, 3                                   ;Asigna 3 al contador
    
        mov dx, offset mensaje                      ;Asigna dirección inicial de mensaje a DX, no su contenido
        mov ah, 9                                   ;Asigna funcion 9 de la INT 21h
repite: jcxz sigue                                  ;Salta a la linea etiquetada con sigue si CX es 0

        int 21h                                     ;Aparece mensaje en pantalla
        dec cx                                      ;Decrementa el valor de CX en 1
        jmp repite                                  ;Salta a la linea etiquetada con repite

sigue:  mov ax, 4ch                                 ;Asigna la funcion 4ch de la INT 21h a AX y con la
        int 21h                                     ;INT 21h se devuelve el control al DOS
        
inicio endp                                        ;Fin del procedimiento
codigo ends                                        ;Fin del segmento
       end inicio                                  ;Fin del programa
