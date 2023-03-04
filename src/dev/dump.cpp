#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

// Define the main function to check the heap memory
int main() {

    // Define the size of the heap memory block to check
    size_t size = 1024;

    // Allocate a block of memory on the heap
    void* ptr = malloc(size);

    // Check if the memory allocation was successful
    if (ptr == NULL) {
        cerr << "Error: Failed to allocate memory" << endl;
        return EXIT_FAILURE;
    }

    // Print the size of the allocated memory block
    cout << "Allocated " << size << " bytes of memory on the heap" << endl;

    // Initialize the memory block with a known value
    memset(ptr, 0xCC, size);

    // Verify that the memory block was initialized correctly
    for (size_t i = 0; i < size; i++) {
        if (*(reinterpret_cast<unsigned char*>(ptr) + i) != 0xCC) {
            cerr << "Error: Memory block initialization failed" << endl;
            free(ptr);
            return EXIT_FAILURE;
        }
    }

    // Deallocate the memory block
    free(ptr);

    // Print a success message
    cout << "Heap memory check passed" << endl;

    // Return success
    return EXIT_SUCCESS;
}
