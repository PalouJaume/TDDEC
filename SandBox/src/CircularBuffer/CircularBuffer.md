# TEST LIST

## Requisitos

Array de tamaño fijo, dos índices (head y tail), un contador de elementos (o alternativamente usar la diferencia entre índices), y el tamaño máximo del buffer.

El primer elemento en entrar es el primero en salir. tail apunta donde se escribe el próximo dato y head apunta donde se lee el próximo dato.

Se trabajar con datos tipo int.

### Operaciones básicas

- Enqueue (write/push): Escribe en tail, luego avanza tail = (tail + 1) % capacity. Falla o sobreescribe si está lleno, según la política elegida.
- Dequeue (read/pop): Lee desde head, luego avanza head = (head + 1) % capacity. Falla si está vacío.
- Peek: Lee desde head sin avanzar el índice.

## Lista de test
Write a test list for a first-in first-out CircularBuffer that holds a series of ints.

1. El BufferCircular esta vacio al inicializarse. (EmptyIntTest)
2. Se puede meter un dato. (WriteIntTest)
3. Se puede leer un dato sin sacarlo. (PeekIntTest)
4. Se puede sacar un dato. (ReadIntTest)

