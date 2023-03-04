#ifndef GLOBAL_SHELL_INDEX_H
#define GLOBAL_SHELL_INDEX_H

#include <iostream>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <sstream>

class GlobalShellIndex {
public:
    GlobalShellIndex();
    ~GlobalShellIndex();
    void printSystemInfo();
    void* allocate(size_t size);
    void deallocate(void* ptr);
    void resize(void* ptr, size_t newSize);
    void printProcessIDs();

private:
    struct Block {
        size_t size;
        bool free;
        Block* next;
    };
    void* m_heap;
    Block* m_firstBlock;
};

GlobalShellIndex::GlobalShellIndex() {
    m_heap = malloc(1);
    m_firstBlock = reinterpret_cast<Block*>(m_heap);
    m_firstBlock->size = 0;
    m_firstBlock->free = true;
    m_firstBlock->next = nullptr;
}

GlobalShellIndex::~GlobalShellIndex() {
    free(m_heap);
}

void GlobalShellIndex::printSystemInfo() {
    std::cout << "System information:\n";
    struct sysinfo si;
    sysinfo(&si);
    std::cout << "  Total RAM: " << si.totalram / (1024 * 1024) << " MB\n";
    std::cout << "  Free RAM: " << si.freeram / (1024 * 1024) << " MB\n";
    std::cout << "  Number of processes: " << si.procs << "\n";
}

void* GlobalShellIndex::allocate(size_t size) {
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
    // Merge adjacent free blocks
    Block* prevBlock = nullptr;
    Block* nextBlock = block->next;
    while (nextBlock != nullptr && nextBlock->free) {
        block->size += nextBlock->size + sizeof(Block);
        block->next = nextBlock->next;
        nextBlock = block->next;
    }
    if (prevBlock != nullptr && prevBlock->free) {
        prevBlock->size += block->size + sizeof(Block);
        prevBlock->next = block->next;
    }
}

void GlobalShellIndex::resize(void* ptr, size_t newSize) {
    // Find the block corresponding to the given pointer
    Block* block = reinterpret_cast<Block*>(reinterpret_cast<char*>(ptr) - sizeof(Block));

    // If the new size is smaller, just shrink the block
    if (newSize < block->size) {
        size_t diff = block->size - newSize;
        if (diff >= sizeof(Block)) {
            Block* newBlock = reinterpret_cast<Block*>(reinterpret_cast<char*>(block) + newSize + sizeof(Block));
            newBlock->size = diff - sizeof(Block);
            newBlock->free = true;
            newBlock->next = block->next;
            block->size = newSize;
            block->next = newBlock;
        }
        else {
            block->size = newSize;
        }
    }
    else if (newSize > block->size) {
        // Try to expand the block by merging with the next block
        Block* nextBlock = block->next;
        if (nextBlock != nullptr && nextBlock->free && block->size + nextBlock->size + sizeof(Block) >= newSize) {
            size_t diff = block->size + nextBlock->size + sizeof(Block) - newSize;
            if (diff >= sizeof(Block)) {
                Block* newBlock = reinterpret_cast<Block*>(reinterpret_cast<char*>(nextBlock) + newSize - sizeof(Block));
                newBlock->size = diff - sizeof(Block);
                newBlock->free = true;
                newBlock->next = nextBlock->next;
                block->size = newSize;
                block->next = newBlock;
            }
            else {
                block->size = newSize;
                block->next = nextBlock->next;
            }
            block->free = false;
        }
        else {
            // Allocate a new block and copy the contents of the old block into it
            void* newPtr = allocate(newSize);
            std::memcpy(newPtr, ptr, block->size);
            deallocate(ptr);
            ptr = newPtr;
        }
    }
}

void GlobalShellIndex::printProcessIDs() {
    std::vector<pid_t> pids;
    DIR* proc = opendir("/proc");
    if (proc == nullptr) {
        std::cout << "Error: could not open /proc directory\n";
        return;
    }
    struct dirent* entry;
    while ((entry = readdir(proc)) != nullptr) {
        if (std::isdigit(entry->d_name[0])) {
            pid_t pid = std::stoi(entry->d_name);
            pids.push_back(pid);
        }
    }
    closedir(proc);
    std::cout << "Process IDs:\n";
    for (pid_t pid : pids) {
        std::string statusPath = "/proc/" + std::to_string(pid) + "/status";
        std::ifstream statusFile(statusPath);
        if (statusFile.is_open()) {
            std::string line;
            while (std::getline(statusFile, line)) {
                    break;
                }
            }
            statusFile.close();
        }
    }
}

void GlobalShellIndex::printSystemInfo() {
    std::cout << "System Information:\n";
    std::cout << "CPU Cores: " << std::thread::hardware_concurrency() << "\n";

    struct utsname unameData;
    if (uname(&unameData) == 0) {
        std::cout << "Operating System: " << unameData.sysname << " " << unameData.release << " " << unameData.machine << "\n";
    }
    else {
        std::cout << "Error: could not retrieve system information\n";
    }

    struct sysinfo sysInfoData;
    if (sysinfo(&sysInfoData) == 0) {
        std::cout << "Total RAM: " << (sysInfoData.totalram / 1024 / 1024) << " MB\n";
        std::cout << "Free RAM: " << (sysInfoData.freeram / 1024 / 1024) << " MB\n";
        std::cout << "Used RAM: " << ((sysInfoData.totalram - sysInfoData.freeram) / 1024 / 1024) << " MB\n";
        std::cout << "Total Swap: " << (sysInfoData.totalswap / 1024 / 1024) << " MB\n";
        std::cout << "Free Swap: " << (sysInfoData.freeswap / 1024 / 1024) << " MB\n";
        std::cout << "Used Swap: " << ((sysInfoData.totalswap - sysInfoData.freeswap) / 1024 / 1024) << " MB\n";
    }
    else {
        std::cout << "Error: could not retrieve system information\n";
    }
}

}  // namespace laux
