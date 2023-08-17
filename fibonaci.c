#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    enum TypeTag {
        ADD,
        SUB,
        MUL,
        FIBO
    } type;
    int operand1;
    int operand2;
} Node;

typedef struct MemoizedResult {
    int value;
    int calculated;
} MemoizedResult;

MemoizedResult memo[100];

// Function to create a Node with the specified type and operands
Node* makeFunc(enum TypeTag type, int operand1, int operand2) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->type = type;
    node->operand1 = operand1;
    node->operand2 = operand2;
    return node;
}

// Function to perform arithmetic operations
int performOperation(enum TypeTag operation, int a, int b) {
    switch (operation) {
        case ADD: return a + b;
        case SUB: return a - b;
        case MUL: return a * b;
        default: return 0;
    }
}

// Function to calculate Fibonacci using memoization
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }

    if (memo[n].calculated) {
        return memo[n].value;
    }

    memo[n].value = fibonacci(n - 1) + fibonacci(n - 2);
    memo[n].calculated = 1;

    return memo[n].value;
}

// Function to perform calculations based on the Node type
void calc(Node* node) {
    if (node->type == FIBO) {
        int fiboValue = fibonacci(3); // Calculate Fibonacci for n=3
        printf("fibo : %d\n", fiboValue);
    } else if (node->type == ADD || node->type == SUB || node->type == MUL) {
        int a = node->operand1;
        int b = node->operand2;

        int result = performOperation(node->type, a, b);
        if (node->type == ADD) {
            printf("add : %d\n", result);
        } else if (node->type == SUB) {
            printf("sub : %d\n", result);
        } else if (node->type == MUL) {
            printf("mul : %d\n", result);
        }
    }
}

int main() {
    // Create Node instances with specified types and operands
    Node* add = makeFunc(ADD, 10, 6);
    Node* mul = makeFunc(MUL, 5, 4);
    Node* sub = makeFunc(SUB, 0, 0); // Operands will be set later
    Node* fibo = makeFunc(FIBO, 0, 0);

    // Set operands for the 'sub' Node
    sub->operand1 = add->operand1;
    sub->operand2 = mul->operand1;

    // Perform calculations and print results
    calc(add);
    calc(mul);
    calc(sub);
    calc(fibo);

    // Free allocated memory
    free(add);
    free(mul);
    free(sub);
    free(fibo);

    return 0;
}
