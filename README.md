# Proyecto Módulo 3 – Acelerador de Funciones
**Materia:** Lenguajes de Interfaz  
**Alumno:** Oscar Sebastián Valdez Barrios  
**Número de control:** 23490625  
**Opción:** A – Contador de Bits (Population Count)

## Descripción
El objetivo del proyecto es comparar el rendimiento de una función escrita en C con una implementación equivalente en ensamblador inline de 64 bits, encargadas de contar la cantidad de bits encendidos (valor 1) en un número entero de 64 bits.

La implementación en ensamblador utiliza el algoritmo **SWAR (SIMD Within A Register)**, que permite realizar el conteo de bits en paralelo mediante operaciones aritméticas, desplazamientos y máscaras binarias.

## Funcionamiento
Se ejecutan 100 millones de iteraciones utilizando los mismos datos para ambas implementaciones:

- `contar_bits_c`: realiza el conteo mediante operaciones y desplazamientos en un ciclo.
- `contar_bits_asm`: utiliza instrucciones de ensamblador x86-64 y el algoritmo SWAR para contar varios bits simultáneamente.

Al finalizar, se comparan los resultados y los tiempos de ejecución de ambas funciones.

## Compilación
Se utilizó GCC 16.2.0 para arquitectura x86-64.

```bash
gcc -O0 -Wall -Wextra proyecto3_swar.c -o proyecto3_swar.exe
```

## Ejecución

```bash
./proyecto3_swar.exe
```

## Resultados obtenidos

| Medición | Resultado |
|---|---:|
| Total en C | 1,500,043,268 |
| Total en ASM | 1,500,043,268 |
| Tiempo en C | 3.9020 s |
| Tiempo en ASM | 0.2410 s |
| Mejora | 16.19x |

Los resultados de ambas implementaciones coinciden, comprobando que realizan correctamente la misma operación.

## Conclusión
La implementación en ensamblador mediante el algoritmo SWAR obtuvo un rendimiento considerablemente superior al de la función en C. Se consiguió una mejora de 16.19 veces en el tiempo de ejecución, demostrando cómo el uso de operaciones de bajo nivel y el procesamiento paralelo dentro de un registro pueden optimizar una tarea repetitiva.