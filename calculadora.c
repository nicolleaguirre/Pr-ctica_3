#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_STACK_SIZE 8

typedef struct {
    double items[MAX_STACK_SIZE];
    int top;
} Stack;

void initialize(Stack *s) {
    s->top = -1;
}

int isFull(Stack *s) {
    return s->top == MAX_STACK_SIZE - 1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, double value) {
    if (isFull(s)) {
        printf("Error: Pila llena. No se puede insertar %f\n", value);
    } else {
        s->items[++(s->top)] = value;
    }
}

double pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Error: Pila vacia.\n");
        return 0.0; // Retornar 0 si la pila está vacía
    } else {
        return s->items[(s->top)--];
    }
}

void printStack(Stack *s) {
    printf("////////Calculadora RPN///////\n");
    for (int i = MAX_STACK_SIZE - 1; i >= 0; i--) {
        if (i > s->top) {
            printf("%d. 0.000000\n", i + 1);
        } else {
            printf("%d. %.6f\n", i + 1, s->items[s->top - i]);
        }
    }
}

void performOperation(Stack *s, char op) {
    if (s->top < 1 && op != 'r' && op != 's' && op != 'c' && op != 't') { // Necesitamos al menos dos elementos para una operación, excepto para operaciones unarias
        printf("No hay suficientes valores en la pila para realizar la operacion.\n");
        return;
    }

    double a, b = 0, result = 0;
    a = pop(s);
    if (op != 'r' && op != 's' && op != 'c' && op != 't') {
        if (!isEmpty(s)) {
            b = pop(s);
        } else {
            printf("Operacion requiere dos operandos. Devolviendo el valor a la pila.\n");
            push(s, a);
            return;
        }
    }

    switch (op) {
        case '+': result = a + b; break;
        case '-': result = b - a; break; // Nota el orden para la resta
        case '*': result = a * b; break;
        case '/':
            if (a == 0) {
                printf("Error: División por cero.\n");
                push(s, b); // Devolvemos el otro valor a la pila
                return;
            }
            result = b / a;
            break;
        case 'r': result = sqrt(a); break;
        case 's': result = sin(a); break;
        case 'c': result = cos(a); break;
        case 't': result = tan(a); break;
        case 'p': result = pow(b, a); break; // Nota el orden para la potencia
        default: printf("Operación no reconocida.\n"); return;
    }

    push(s, result);
}

int main() {
    Stack stack;
    initialize(&stack);
    char option;
    double num;

    do {
        printStack(&stack);
        printf("\nSeleccione la opcion a realizar:\n");
        printf("1. Ingrese numero\n");
        printf("2. Seleccione operacion (+, -, *, /, r(raiz), s(seno), c(coseno), t(tangente), p(potencia))\n");
        printf("3. Limpiar ultimo registro\n");
        printf("4. Limpiar todos los registros\n");
        printf("5. Salir\n");
        printf("Opcion: ");
        scanf(" %c", &option);

        switch (option) {
            case '1':
                if (isFull(&stack)) {
                    printf("Pila llena. No se puede ingresar más números.\n");
                } else {
                    printf("Ingrese un numero: ");
                    scanf("%lf", &num);
                    push(&stack, num);
                }
                break;
            case '2':
                printf("Seleccione una operacion (+, -, *, /, r, s, c, t, p): ");
                scanf(" %c", &option);
                performOperation(&stack, option);
                break;
            case '3':
                if (!isEmpty(&stack)) {
                    pop(&stack);
                } else {
                    printf("Pila ya esta vacia.\n");
                }
                break;
            case '4':
                initialize(&stack); // Esto limpiará todos los registros reiniciando la pila
                break;
            case '5':
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no valida.\n");
        }
    } while (option != '5');

    return 0;
}
      