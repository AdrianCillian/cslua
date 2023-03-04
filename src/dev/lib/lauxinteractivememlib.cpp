#ifndef GLOBALMEMORYHEAP_H
#define GLOBALMEMORYHEAP_H

#include <iostream>
#include <Windows.h>

class GlobalMemoryHeap {
private:
    DWORD_PTR m_heapBaseAddr; // Base address of heap
    DWORD_PTR m_heapEndAddr; // End address of heap
public:
    GlobalMemoryHeap() : m_heapBaseAddr(0), m_heapEndAddr(0) {}
    ~GlobalMemoryHeap() {}

    void heapMemory() {
        // Heap memory allocation
        m_heapBaseAddr = reinterpret_cast<DWORD_PTR>(HeapAlloc(GetProcessHeap(), 0, 1024 * 1024));
        if (m_heapBaseAddr == NULL) {
            std::cout << "Heap allocation failed" << std::endl;
            return;
        }

        // Output heap memory base and end addresses to console
        std::cout << "Heap Memory Base Address: 0x" << std::hex << m_heapBaseAddr << std::endl;

        // Calculate heap end address
        m_heapEndAddr = m_heapBaseAddr + 1024 * 1024;
        std::cout << "Heap Memory End Address: 0x" << std::hex << m_heapEndAddr << std::endl;
    }

    void rebaseAddresses() {
        // Get current process ID
        DWORD currentProcessId = GetCurrentProcessId();
        std::cout << "Process ID: " << currentProcessId << std::endl;

        // Get module handle for this process
        HMODULE moduleHandle = GetModuleHandle(NULL);

        // Get module base address
        DWORD_PTR moduleBaseAddr = reinterpret_cast<DWORD_PTR>(moduleHandle);
        std::cout << "Module Base Address: 0x" << std::hex << moduleBaseAddr << std::endl;

        // Get current thread ID
        DWORD currentThreadId = GetCurrentThreadId();
        std::cout << "Thread ID: " << currentThreadId << std::endl;

        // Get current fiber ID
        DWORD currentFiberId = GetCurrentFiberId();
        std::cout << "Fiber ID: " << currentFiberId << std::endl;

        // Get heap base and end addresses
        std::cout << "Heap Memory Base Address: 0x" << std::hex << m_heapBaseAddr << std::endl;
        std::cout << "Heap Memory End Address: 0x" << std::hex << m_heapEndAddr << std::endl;
    }
};

#endif // GLOBALMEMORYHEAP_H
