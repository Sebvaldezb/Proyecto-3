// ============================================================
// PROYECTO MODULO 3: ACELERADOR DE FUNCIONES
// Problema: Contador de Bits (Population Count)
// Opcion A - GCC / MinGW x86-64
// Version optimizada mediante conteo paralelo de bits (SWAR)
// ============================================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000000   // 100 millones de iteraciones

// ------------------------------------------------------------
// VERSION EN C PURO (NO MODIFICAR)
// ------------------------------------------------------------
int contar_bits_c(unsigned long long n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

// ------------------------------------------------------------
// VERSION EN ENSAMBLADOR INLINE
// ------------------------------------------------------------
int contar_bits_asm(unsigned long long n) {
    int count = 0;

    asm volatile (
        "movq %1, %%rax\n\t"

        // Paso 1: contar bits por parejas.
        "movabsq $0x5555555555555555, %%rcx\n\t"
        "movq %%rax, %%rdx\n\t"
        "shrq $1, %%rdx\n\t"
        "andq %%rcx, %%rdx\n\t"
        "subq %%rdx, %%rax\n\t"

        // Paso 2: sumar grupos de dos bits.
        "movabsq $0x3333333333333333, %%rcx\n\t"
        "movq %%rax, %%rdx\n\t"
        "shrq $2, %%rdx\n\t"
        "andq %%rcx, %%rax\n\t"
        "andq %%rcx, %%rdx\n\t"
        "addq %%rdx, %%rax\n\t"

        // Paso 3: sumar grupos de cuatro bits.
        "movabsq $0x0F0F0F0F0F0F0F0F, %%rcx\n\t"
        "movq %%rax, %%rdx\n\t"
        "shrq $4, %%rdx\n\t"
        "addq %%rdx, %%rax\n\t"
        "andq %%rcx, %%rax\n\t"

        // Paso 4: acumular los grupos restantes.
        "movq %%rax, %%rdx\n\t"
        "shrq $8, %%rdx\n\t"
        "addq %%rdx, %%rax\n\t"

        "movq %%rax, %%rdx\n\t"
        "shrq $16, %%rdx\n\t"
        "addq %%rdx, %%rax\n\t"

        "movq %%rax, %%rdx\n\t"
        "shrq $32, %%rdx\n\t"
        "addq %%rdx, %%rax\n\t"

        // Los siete bits inferiores contienen el resultado (0 a 64).
        "andl $0x7F, %%eax\n\t"
        "movl %%eax, %0\n\t"

        : "=&r" (count)
        : "r" (n)
        : "rax", "rcx", "rdx", "cc"
    );

    return count;
}

// ------------------------------------------------------------
// FUNCION PRINCIPAL (ESTRUCTURA DEL STUB DEL PROFESOR)
// ------------------------------------------------------------
int main() {
    // Semilla para numeros aleatorios
    srand(42);

    // Crear arreglo de numeros aleatorios
    unsigned long long *arr = (unsigned long long*)malloc(N * sizeof(unsigned long long));
    if (arr == NULL) {
        printf("Error: no se pudo reservar memoria.\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        arr[i] = ((unsigned long long)rand() << 32) | rand();
    }

    // Medir tiempo en C
    clock_t inicio = clock();
    long long total_c = 0;
    for (int i = 0; i < N; i++) {
        total_c += contar_bits_c(arr[i]);
    }
    clock_t fin = clock();
    double tiempo_c = (double)(fin - inicio) / CLOCKS_PER_SEC;

    // Medir tiempo en ASM
    inicio = clock();
    long long total_asm = 0;
    for (int i = 0; i < N; i++) {
        total_asm += contar_bits_asm(arr[i]);
    }
    fin = clock();
    double tiempo_asm = (double)(fin - inicio) / CLOCKS_PER_SEC;

    // Verificar que los resultados son iguales
    printf("Total en C:   %lld\n", total_c);
    printf("Total en ASM: %lld\n", total_asm);

    if (total_c == total_asm) {
        printf("   Los resultados coinciden.\n");
    } else {
        printf("   ERROR: Los resultados NO coinciden.\n");
    }

    // Mostrar tiempos
    printf("\nTiempo en C:   %.4f s\n", tiempo_c);
    printf("Tiempo en ASM: %.4f s\n", tiempo_asm);

    if (tiempo_asm > 0.0) {
        printf("Mejora: %.2fx\n", tiempo_c / tiempo_asm);
    } else {
        printf("Mejora: no disponible (tiempo ASM igual a cero).\n");
    }

    free(arr);
    return 0;
}
