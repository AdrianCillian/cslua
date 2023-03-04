#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lua.hpp>

extern "C" {

  // Define the cslua functions
  __declspec(dllexport) int cslua_open(lua_State* L) {
    
    return 0;
  }

  __declspec(dllexport) int cslua_close(lua_State* L) {
    
    return 0;
  }

  __declspec(dllexport) int cslua_dostring(lua_State* L, const char* str) {
    
    return 0;
  }

  __declspec(dllexport) int cslua_dofile(lua_State* L, const char* filename) {
    
    return 0;
  }

  __declspec(dllexport) int cslua_newstate(lua_State* L) {
    
    return 0;
  }

  __declspec(dllexport) int cslua_load(lua_State* L, const char* chunk, size_t len, const char* name) {
    
    return 0;
  }

  __declspec(dllexport) int cslua_dump(lua_State* L, lua_Writer writer, void* data) {
    
    return 0;
  }

  __declspec(dllexport) void cslua_createtable(lua_State* L, int narr, int nrec) {
    
  }

  __declspec(dllexport) void cslua_newtable(lua_State* L) {
    
  }

  __declspec(dllexport) void cslua_settable(lua_State* L, int idx) {
    
  }

  __declspec(dllexport) void cslua_gettable(lua_State* L, int idx) {
    
  }

  __declspec(dllexport) void cslua_setglobal(lua_State* L, const char* name) {
    
  }

  __declspec(dllexport) void cslua_getglobal(lua_State* L, const char* name) {
    
  }

  __declspec(dllexport) int cslua_type(lua_State* L, int idx) {
    
    return 0;
  }

  __declspec(dllexport) int cslua_isnumber(lua_State* L, int idx) {
    
    return 0;
  }

  __declspec(dllexport) int cslua_isstring(lua_State* L, int idx) {
    
    return 0;
  }

  __declspec(dllexport) int cslua_iscfunction(lua_State* L, int idx) {
    
    return 0;
  }

  __declspec(dllexport) int cslua_isuserdata(lua_State* L, int idx) {
    
    return 0;
  }

  __declspec(dllexport) int cslua_isnil(lua_State* L, int idx) {
    
    return 0;
  }

  __declspec(dllexport) int cslua_isboolean(lua_State* L, int idx) {
    
    return 0;
  }

  __declspec(dllexport) int cslua_istable(lua_State* L, int idx) {
    
    return 0;
  }
