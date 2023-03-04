#ifndef REDUX_CSLUA_H
#define REDUX_CSLUA_H

#include <lua.hpp>

namespace rodux_cslua {

    // Pushes the version of Redux CSLua to the Lua stack
    int version(lua_State* L);

    // Executes the specified Lua code
    int execute(lua_State* L);

    // Executes a file containing Lua code
    int executeFile(lua_State* L);

    // Retrieves the value of a global variable
    int getGlobal(lua_State* L);

    // Sets the value of a global variable
    int setGlobal(lua_State* L);

    // Loads a Lua module
    int require(lua_State* L);

    // Returns the memory usage of Lua
    int memoryUsage(lua_State* L);

    // Returns the total memory in use by Lua
    int totalMemory(lua_State* L);

    // Collects garbage
    int collectGarbage(lua_State* L);

    // Returns the type of the value at the specified stack index
    int typeOf(lua_State* L);

    // Returns the length of a table
    int tableLength(lua_State* L);

    // Iterates over the key-value pairs of a table
    int tablePairs(lua_State* L);

    // Inserts a new element into a table
    int tableInsert(lua_State* L);

    // Removes an element from a table
    int tableRemove(lua_State* L);

    // Converts a Lua value to a string
    int toString(lua_State* L);

    // Converts a Lua value to a number
    int toNumber(lua_State* L);

    // Converts a Lua value to a boolean
    int toBoolean(lua_State* L);

    // Converts a Lua value to a C function
    int toFunction(lua_State* L);

    // Converts a Lua value to a C pointer
    int toPointer(lua_State* L);

    // Converts a Lua value to a C++ object
    int toObject(lua_State* L);

    // Pushes a C++ object onto the Lua stack
    template<typename T>
    void pushObject(lua_State* L, T* obj);

    // Retrieves a C++ object from the Lua stack
    template<typename T>
    T* getObject(lua_State* L, int index);

} // namespace rodux_cslua

// Concatenates the top n values on the stack, separated by the given delimiter
int rodux_cslua_concat(lua_State* L, const char* delimiter, int n) {
    if (n <= 0) {
        lua_pushstring(L, "");
        return 1;
    }
    luaL_Buffer b;
    luaL_buffinit(L, &b);
    for (int i = 1; i <= n; i++) {
        const char* s = luaL_tolstring(L, i, NULL);
        if (s == NULL) {
            luaL_error(L, "'tostring' must return a string to 'concat'");
        }
        luaL_addstring(&b, s);
        if (i != n) {
            luaL_addstring(&b, delimiter);
        }
        lua_pop(L, 1);
    }
    luaL_pushresult(&b);
    return 1;
}

// Splits a string into multiple substrings based on the given delimiter
int rodux_cslua_split(lua_State* L) {
    const char* s = luaL_checkstring(L, 1);
    const char* delimiter = luaL_checkstring(L, 2);

    lua_newtable(L);
    int table_index = 1;

    const char* start = s;
    while (*s) {
        if (*s == *delimiter) {
            lua_pushlstring(L, start, s - start);
            lua_rawseti(L, -2, table_index++);
            start = s + 1;
        }
        s++;
    }

    lua_pushstring(L, start);
    lua_rawseti(L, -2, table_index);

    return 1;
}

// Creates a new table with the given keys and values
int rodux_cslua_table(lua_State* L, int nkeys, int nvalues) {
    lua_createtable(L, 0, nkeys + nvalues);
    for (int i = 1; i <= nkeys; i++) {
        lua_pushvalue(L, -nkeys - 1);
        lua_rawseti(L, -2, i);
    }
    for (int i = 1; i <= nvalues; i++) {
        lua_pushvalue(L, -nvalues - 1);
        lua_rawseti(L, -2, i + nkeys);
    }
    return 1;
}

// Returns the size of the table at the given index
int rodux_cslua_table_size(lua_State* L, int index) {
    int count = 0;
    lua_pushnil(L);
    while (lua_next(L, index)) {
        count++;
        lua_pop(L, 1);
    }
    return count;
}

// Returns a copy of the table at the given index
int rodux_cslua_table_copy(lua_State* L, int index) {
    int n = rodux_cslua_table_size(L, index);
    lua_createtable(L, n, 0);
    lua_pushnil(L);
    while (lua_next(L, index)) {
        lua_pushvalue(L, -2);
        lua_insert(L, -2);
        lua_rawset(L, -3);
    }
    return 1;
}

// Returns a table containing the keys of the table at the given index
int rodux_cslua_table_keys(lua_State* L, int index) {
luaL_checktype(L, index, LUA_TTABLE);
lua_newtable(L);
int table_index = 1;
lua_pushnil(L);
while (lua_next(L, index)) {
lua_pushvalue(L, -2);
lua_rawseti(L, -2, table_index++);
lua_pop(L, 1);
}
return 1;
}

// Returns a table containing the values of the table at the given index
int rodux_cslua_table_values(lua_State* L, int index) {
luaL_checktype(L, index, LUA_TTABLE);
lua_newtable(L);
int table_index = 1;
lua_pushnil(L);
while (lua_next(L, index)) {
lua_pushvalue(L, -1);
lua_rawseti(L, -2, table_index++);
lua_pop(L, 1);
}
return 1;
}

// Reverses the order of the elements in a table at the given index
int rodux_cslua_table_reverse(lua_State* L, int index) {
luaL_checktype(L, index, LUA_TTABLE);
int len = rodux_cslua_table_size(L, index);
for (int i = 1; i <= len / 2; i++) {
lua_rawgeti(L, index, i);
lua_rawgeti(L, index, len - i + 1);
lua_rawseti(L, index, i);
lua_rawseti(L, index, len - i + 1);
}
return 0;
}

// Returns a sorted copy of the table at the given index
int rodux_cslua_table_sort(lua_State* L, int index) {
luaL_checktype(L, index, LUA_TTABLE);
lua_newtable(L);
int len = rodux_cslua_table_size(L, index);
lua_rawgeti(L, index, 1);
for (int i = 1; i <= len; i++) {
int j = i - 1;
lua_pushvalue(L, -1);
lua_rawgeti(L, index, i + 1);
while (j >= 0 && lua_compare(L, -2, -1, LUA_OPLT)) {
lua_rawgeti(L, -4, j + 1);
lua_rawseti(L, -3, j + 2);
j--;
}
lua_pop(L, 2);
lua_rawseti(L, -2, j + 2);
lua_rawgeti(L, index, i + 1);
}
return 1;
}

// Returns a new table with the values of the given table transformed by the given function
int rodux_cslua_table_map(lua_State* L, int index, lua_CFunction transform) {
luaL_checktype(L, index, LUA_TTABLE);
lua_newtable(L);
int table_index = 1;
lua_pushnil(L);
while (lua_next(L, index)) {
lua_pushvalue(L, -1);
lua_call(L, 1, 1);
lua_rawseti(L, -2, table_index++);
lua_pop(L, 1);
}
return 1;
}

// Returns true if the table at the given index contains the given value
int rodux_cslua_table_contains(lua_State* L, int index, lua_Integer value) {
luaL_checktype(L, index, LUA_TTABLE);
lua_pushinteger(L, value);
#endif // REDUX_CSLUA_H
