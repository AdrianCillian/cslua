#ifndef LAUXHEAPLOADER_HPP
#define LAUXHEAPLOADER_HPP

#include <iostream>
#include <cstring>

class HeapLoader {
public:
    HeapLoader();
    ~HeapLoader();
    void* allocate(size_t size);
    void deallocate(void* ptr);
    void resize(void* ptr, size_t newSize);
    void print();

private:
    struct Block {
        size_t size;
        bool free;
        Block* next;
    };
    void* m_heap;
    Block* m_firstBlock;
};

HeapLoader::HeapLoader() {
    m_heap = malloc(1);
    m_firstBlock = reinterpret_cast<Block*>(m_heap);
    m_firstBlock->size = 0;
    m_firstBlock->free = true;
    m_firstBlock->next = nullptr;
}

HeapLoader::~HeapLoader() {
    free(m_heap);
}

void* HeapLoader::allocate(size_t size) {
    // Find a free block of sufficient size
    Block* block = m_firstBlock;
    Block* prevBlock = nullptr;
    while (block != nullptr) {
        if (block->free && block->size >= size) {
            break;
        }
        prevBlock = block;
        block = block->next;
    }

    // If no block is found, allocate a new block
    if (block == nullptr) {
        void* ptr = malloc(size + sizeof(Block));
        block = reinterpret_cast<Block*>(ptr);
        block->size = size;
        block->free = false;
        block->next = nullptr;
        if (prevBlock != nullptr) {
            prevBlock->next = block;
        }
        else {
            m_firstBlock = block;
        }
    }
    else {
        // Split the block if it's too large
        if (block->size > size + sizeof(Block)) {
            Block* newBlock = reinterpret_cast<Block*>(reinterpret_cast<char*>(block) + size + sizeof(Block));
            newBlock->size = block->size - size - sizeof(Block);
            newBlock->free = true;
            newBlock->next = block->next;
            block->size = size;
            block->free = false;
            block->next = newBlock;
            if (prevBlock != nullptr) {
                prevBlock->next = block;
            }
            else {
                m_firstBlock = block;
            }
        }
        else {
            block->free = false;
        }
    }

    // Return a pointer to the allocated memory
    return reinterpret_cast<char*>(block) + sizeof(Block);
}

void HeapLoader::deallocate(void* ptr) {
    // Find the block corresponding to the given pointer
    Block* block = reinterpret_cast<Block*>(reinterpret_cast<char*>(ptr) - sizeof(Block));
    block->free = true;

    // Merge contiguous free blocks
    Block* prevBlock = nullptr;
    Block* nextBlock = m_firstBlock;
    while (nextBlock != nullptr) {
        if (prevBlock != nullptr && prevBlock->free && nextBlock->free) {
            prevBlock->size += nextBlock->size + sizeof(Block);
            prevBlock->next = nextBlock->next;
            nextBlock = prevBlock;
        }
        prevBlock = nextBlock;
        nextBlock = nextBlock->next;
    }
}

void HeapLoader::resize(void* ptr, size_t newSize) {
    // Find the block corresponding to the given pointer
    Block* block = reinterpret_cast<Block*>(reinterpret_cast<char*>(ptr) - sizeof(Block));
