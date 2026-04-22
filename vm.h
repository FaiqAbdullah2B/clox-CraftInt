#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"

#define STACK_MAX 256

typedef struct{
    Chunk *chunk;
    uint8_t *ip; // Points at the instruction about to be executed.
    Value stack[STACK_MAX];
    Value *stackTop; // Points to the value just above the top of the stack.
    Obj* objects; // head of the list
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

extern VM vm;

void initVM(void);
void freeVM(void);

InterpretResult interpret(const char* source);

void push(Value value);
Value pop(void);

#endif