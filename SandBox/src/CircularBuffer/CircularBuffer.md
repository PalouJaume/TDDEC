# TEST LIST

## Requisitos

Array de tamaño fijo, dos índices (head y tail), un contador de elementos (o alternativamente usar la diferencia entre índices), y el tamaño máximo del buffer.

El primer elemento en entrar es el primero en salir. tail apunta donde se escribe el próximo dato y head apunta donde se lee el próximo dato.

Se trabajar con datos tipo int.

### Operaciones básicas

- Enqueue (write/push): Escribe en tail, luego avanza tail = (tail + 1) % capacity. Sobreescribe si está lleno, según la política elegida.
- Dequeue (read/pop): Lee desde head, luego avanza head = (head + 1) % capacity. Falla si está vacío.
- Peek: Lee desde head sin avanzar el índice.
- IsEmpty: retorna 1 si el buffer esta vacio.
- IsFull: retorna 0 si el buffer esta lleno. 
- getNumElements: retorna el número de elementos guardados en el buffer.
- FillWithValue: llena el buffer con el valor dado.
- Clear: Resetea el buffer.


## Lista de test
Write a test list for a first-in first-out CircularBuffer that holds a series of ints.

1. El BufferCircular esta vacio al inicializarse. (EmptyIntTest) [DONE]
2. Se puede meter un dato. (WriteIntTest) [DONE]
3. Se puede leer un dato sin sacarlo. (PeekIntTest) [DONE]
4. Se puede sacar un dato. (ReadIntTest) [DONE]
5. Sobreescribe el dato si esta lleno y hay un write (OverWriteTest) [DONE]
6. Peek no modifica el buffer. (InmutablePeekTest) [DONE]
7. Se pueden hacer multiples escrituras. (MultiplewritesTest) [DONE]
8. Lectura de buffer vacio no mueve los indices (ReadEmptyBufferTest) [DONE]
9. Lectura de estado - Buffer lleno.  [DONE]
10. Lectura de estado - Buffer vacio. [DONE]

