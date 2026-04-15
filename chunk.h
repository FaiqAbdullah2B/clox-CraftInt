#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
    OP_CONSTANT,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_NEGATE,
    OP_RETURN,
} OpCode;

typedef struct {
    int line;
    int count;
} LineRun; // storing line numbers through RLE to save memory

typedef struct {
    int count;
    int capacity;
    uint8_t *code;

    ValueArray constants;

    int lineCount;
    int lineCapacity;
    LineRun *lines;
} Chunk;

void initChunk(Chunk *chunk);
void freeChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);
int getLine(Chunk* chunk, int instructionIndex);

int addConstant(Chunk *chunk, Value value);


#endif