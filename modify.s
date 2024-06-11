section .text
    global modify     ; Hacer la etiqueta 'modify' global para que sea accesible desde C

modify:
    ; Guardar los registros utilizados
    push ebp
    mov ebp, esp

    ; Acceder al par�metro
    mov eax, [ebp + 8]   ; Primer par�metro (int *ptr)

    ; Modificar el valor al que apunta ptr
    mov dword [eax], 1234

    ; Restaurar los registros y volver
    pop ebp
    ret