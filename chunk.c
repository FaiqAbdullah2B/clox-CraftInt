#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk *chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    
    chunk->lineCount = 0;
    chunk->lineCapacity = 0;
    chunk->lines = NULL;

    initValueArray(&chunk->constants);
}

void freeChunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(LineRun, chunk->lines, chunk->lineCapacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
    // growing the chunk array if needed
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code,
            oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->count++;

    // RLE line number encoding logic
    if (chunk->lineCount == 0 || chunk->lines[chunk->lineCount-1].line != line) {
        // very first line or if the line number has changed.
        // checking if the lines array has space for a new entry
        if (chunk->lineCapacity < chunk->lineCount + 1) {
            // resizing the array
            int oldLineCapacity = chunk->lineCapacity;
            chunk->lineCapacity = GROW_CAPACITY(oldLineCapacity);
            chunk->lines = GROW_ARRAY(LineRun, chunk->lines,
                oldLineCapacity, chunk->lineCapacity);
        }

        LineRun* run = &chunk->lines[chunk->lineCount];
        run->line = line;
        run->count = 1;
        chunk->lineCount++;
    } else {
        // increment the latest line count as it's the same
        chunk->lines[chunk->lineCount-1].count++;
    }

    
}

int getLine(Chunk* chunk, int instructionIndex) {
    int currentInstruction = 0;

    for (int i = 0; i < chunk->lineCount; i++) {
        LineRun *run = &chunk->lines[i];
        currentInstruction += run->count;
        if (currentInstruction > instructionIndex) {
            return run->line;
        }
    }

    return -1;
}

int addConstant(Chunk *chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}