#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

// Rust-like Result type
typedef struct {
    bool isOk;
    union {
        void* ok;
        char* err;
    } data;
} RcsluaResult;

// Rust-like Option type
typedef struct {
    bool isSome;
    void* data;
} RcsluaOption;

// Rust-like string type
typedef struct {
    char* data;
    size_t len;
} RcsluaString;

// Rust-like vector type
typedef struct {
    void** data;
    size_t len;
    size_t cap;
} RcsluaVec;

// Rust-like hash map type
typedef struct {
    RcsluaVec* keys;
    RcsluaVec* vals;
} RcsluaHashMap;

// Rust-like Box type
typedef struct {
    void* data;
    size_t size;
} RcsluaBox;

// Rust-like slice type
typedef struct {
    void* data;
    size_t len;
} RcsluaSlice;

// Rust-like integer types
typedef int8_t RcsluaI8;
typedef int16_t RcsluaI16;
typedef int32_t RcsluaI32;
typedef int64_t RcsluaI64;
typedef uint8_t RcsluaU8;
typedef uint16_t RcsluaU16;
typedef uint32_t RcsluaU32;
typedef uint64_t RcsluaU64;

// Rust-like floating point types
typedef float RcsluaF32;
typedef double RcsluaF64;

// Rust-like boolean type
typedef bool RcsluaBool;

// Rust-like unsafe block
#define rcslua_unsafe unsafe

// Rust-like enums
typedef enum {
    RcsluaNone,
    RcsluaSome
} RcsluaOptionTag;

typedef enum {
    RcsluaOk,
    RcsluaErr
} RcsluaResultTag;

// Rust-like functions

RcsluaOption rcslua_option_new(void* data) {
    RcsluaOption option;
    option.isSome = data != NULL;
    option.data = data;
    return option;
}

void rcslua_option_free(RcsluaOption option) {
    if (option.isSome) {
        free(option.data);
    }
}

RcsluaResult rcslua_result_ok(void* data) {
    RcsluaResult result;
    result.isOk = true;
    result.data.ok = data;
    return result;
}

RcsluaResult rcslua_result_err(char* err) {
    RcsluaResult result;
    result.isOk = false;
    result.data.err = err;
    return result;
}

void rcslua_result_free(RcsluaResult result) {
    if (!result.isOk) {
        free(result.data.err);
    }
}

RcsluaString rcslua_string_new(char* data) {
    RcsluaString string;
    string.data = data;
    string.len = strlen(data);
    return string;
}

void rcslua_string_free(RcsluaString string) {
    free(string.data);
}

RcsluaVec rcslua_vec_new(size_t len, size_t elem_size) {
    RcsluaVec vec;
    vec.data = malloc(len * elem_size);
    vec.len = len;
    vec.cap = len;
    return vec;
}
Continuing from the previous code snippet, here are more functions related to Rust and C++ with names starting with "rcslua":

c
Copy code
void rcslua_vec_free(RcsluaVec vec) {
    free(vec.data);
}

void* rcslua_vec_get(RcsluaVec* vec, size_t index) {
    if (index >= vec->len) {
        return NULL;
    }
    return vec->data[index];
}

RcsluaHashMap rcslua_hashmap_new() {
    RcsluaHashMap hashmap;
    hashmap.keys = malloc(sizeof(RcsluaVec));
    hashmap.vals = malloc(sizeof(RcsluaVec));
    *hashmap.keys = rcslua_vec_new(0, sizeof(RcsluaString));
    *hashmap.vals = rcslua_vec_new(0, sizeof(void*));
    return hashmap;
}

void rcslua_hashmap_free(RcsluaHashMap hashmap) {
    rcslua_vec_free(*hashmap.keys);
    rcslua_vec_free(*hashmap.vals);
    free(hashmap.keys);
    free(hashmap.vals);
}

void rcslua_hashmap_insert(RcsluaHashMap* hashmap, RcsluaString key, void* val) {
    size_t index = 0;
    for (size_t i = 0; i < hashmap->keys->len; i++) {
        RcsluaString* existing_key = rcslua_vec_get(hashmap->keys, i);
        if (strcmp(existing_key->data, key.data) == 0) {
            index = i;
            break;
        }
    }
    if (index == 0 && hashmap->keys->len > 0) {
        index = hashmap->keys->len;
        rcslua_vec_push(hashmap->keys, &key);
        rcslua_vec_push(hashmap->vals, &val);
    } else {
        rcslua_vec_set(hashmap->vals, index, &val);
    }
}

void* rcslua_hashmap_get(RcsluaHashMap* hashmap, RcsluaString key) {
    for (size_t i = 0; i < hashmap->keys->len; i++) {
        RcsluaString* existing_key = rcslua_vec_get(hashmap->keys, i);
        if (strcmp(existing_key->data, key.data) == 0) {
            return rcslua_vec_get(hashmap->vals, i);
        }
    }
    return NULL;
}

RcsluaBox rcslua_box_new(void* data, size_t size) {
    RcsluaBox box;
    box.data = malloc(size);
    memcpy(box.data, data, size);
    box.size = size;
    return box;
}

void rcslua_box_free(RcsluaBox box) {
    free(box.data);
}

RcsluaSlice rcslua_slice_new(void* data, size_t len) {
    RcsluaSlice slice;
    slice.data = data;
    slice.len = len;
    return slice;
}

bool rcslua_is_nan(RcsluaF64 val) {
    return isnan(val);
}

bool rcslua_is_inf(RcsluaF64 val) {
    return isinf(val);
}

RcsluaF64 rcslua_f64_abs(RcsluaF64 val) {
    return fabs(val);
}

RcsluaF64 rcslua_f64_ceil(RcsluaF64 val) {
    return ceil(val);
}

RcsluaF64 rcslua_f64_floor(RcsluaF64 val) {
    return floor(val);
}
