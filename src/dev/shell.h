#ifndef CSLUA_SHELL_H
#define CSLUA_SHELL_H

#include "cs-bind.c"
#include "cslua.hpp"

// Define the cslua shell functions
int cslua_open(lua_State* L);
int cslua_close(lua_State* L);
int cslua_dostring(lua_State* L, const char* str);
int cslua_dofile(lua_State* L, const char* filename);
int cslua_newstate(lua_State* L);
int cslua_load(lua_State* L, const char* chunk, size_t len, const char* name);
int cslua_dump(lua_State* L, lua_Writer writer, void* data);
void cslua_createtable(lua_State* L, int narr, int nrec);
void cslua_newtable(lua_State* L);
void cslua_settable(lua_State* L, int idx);
void cslua_gettable(lua_State* L, int idx);
void cslua_setglobal(lua_State* L, const char* name);
void cslua_getglobal(lua_State* L, const char* name);
int cslua_type(lua_State* L, int idx);
int cslua_isnumber(lua_State* L, int idx);
int cslua_isstring(lua_State* L, int idx);
int cslua_iscfunction(lua_State* L, int idx);
int cslua_isuserdata(lua_State* L, int idx);
int cslua_isnil(lua_State* L, int idx);
int cslua_isboolean(lua_State* L, int idx);
int cslua_istable(lua_State* L, int idx);
int cslua_isfunction(lua_State* L, int idx);
int cslua_isthread(lua_State* L, int idx);
int cslua_isnone(lua_State* L, int idx);
int cslua_isnoneornil(lua_State* L, int idx);
lua_Number cslua_tonumber(lua_State* L, int idx);
const char* cslua_tostring(lua_State* L, int idx);
size_t cslua_strlen(lua_State* L, int idx);
lua_CFunction cslua_tocfunction(lua_State* L, int idx);
void* cslua_touserdata(lua_State* L, int idx);
lua_State* cslua_tothread(lua_State* L, int idx);

#endif // CSLUA_SHELL_H
