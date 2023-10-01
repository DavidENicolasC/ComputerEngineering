COMMENT * Escribir un programa que saque en pantalla
          con el formato
          Hola como estan
          con directivas simplificadas. *
        
        .model small             ;Define el modelo de memoria

        .stack                   ;Define el area de la pila

        .data                    ;Area de datos
Mensaje db 'Hola como estan$'    ;Se define la variable Mensaje
        
        .code                    ;Area de codigo
begin:
        mov ax, @data            ;Asigna la dirección del segmento de datos a AX y
        mov ds, ax               ;a traves de AX asigna la dirección de datos a DS
        
        mov dx, offset Mensaje   ;Asigna direccion inicial de Mensaje a DX, no su contenido
        mov ah, 9                ;Asigna funcion 9 de la
        int 21h                  ;INT 21H. (Aparece mensaje en pantalla)
        
        mov ah, 4ch              ;Asigna la funcion 4ch de la INT 21h a AH y con la
        int 21h                  ;INT 21h se devuelve el control al DOS
        
            end begin            ;Fin del programa
