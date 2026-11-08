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

## Uso de ChatGPT como herramienta de apoyo

Durante el desarrollo del proyecto se utilizó ChatGPT como herramienta de apoyo para comprender los conceptos involucrados, investigar alternativas de optimización, implementar la solución en ensamblador y verificar los resultados obtenidos. Se utilizaron principalmente los siguientes prompts:

**1. Comprensión del código C**

> Explica paso a paso cómo funciona la función de conteo de bits en C. Describe el uso de AND, el desplazamiento a la derecha y el ciclo que procesa los 64 bits.

**2. Comprensión de ensamblador inline**

> Explícame cómo funciona el ensamblador inline de GCC para x86-64, cómo se declaran los operandos de entrada y salida y qué función tiene la lista clobber.

**3. Investigación de optimización**

> Investiga métodos para optimizar el conteo de bits de un entero de 64 bits. Compara el recorrido bit por bit con el algoritmo SWAR y explica cómo funciona este último.

**4. Implementación de la solución**

> Ayúdame a implementar la función contar_bits_asm utilizando ensamblador inline x86-64 y el algoritmo SWAR. Conserva la función original en C y el main del profesor. Explica cada instrucción utilizada.

**5. Revisión de resultados**

> Analiza los resultados de ejecución de las versiones C y ASM. Comprueba si los totales coinciden, calcula la mejora de rendimiento y explica qué significan los tiempos obtenidos.

**6. Preparación de la exposición**

> Prepara una explicación técnica del algoritmo SWAR, incluyendo el funcionamiento de las máscaras binarias, los registros utilizados, las instrucciones ASM y las restricciones clobber.

**Nota:** ChatGPT se utilizó como herramienta complementaria para facilitar la comprensión, orientar la implementación y apoyar la revisión del proyecto. La solución final fue revisada y ejecutada para comprobar su funcionamiento.