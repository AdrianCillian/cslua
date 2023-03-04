#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

// cslua functions
int cslua_pushstring(lua_State *L, const char *s);
int cslua_toboolean(lua_State *L, int idx);
int cslua_tointeger(lua_State *L, int idx);
int cslua_tonumber(lua_State *L, int idx);
const char *cslua_tolstring(lua_State *L, int idx, size_t *len);
lua_CFunction cslua_tocfunction(lua_State *L, int idx);
void *cslua_touserdata(lua_State *L, int idx);
lua_State *cslua_tothread(lua_State *L, int idx);
const void *cslua_topointer(lua_State *L, int idx);
void cslua_pushnil(lua_State *L);
void cslua_pushboolean(lua_State *L, int b);
void cslua_pushinteger(lua_State *L, lua_Integer n);
void cslua_pushnumber(lua_State *L, lua_Number n);
void cslua_pushcclosure(lua_State *L, lua_CFunction fn, int n);
void cslua_pushlstring(lua_State *L, const char *s, size_t len);
void cslua_pushvalue(lua_State *L, int idx);
void cslua_pushthread(lua_State *L);
int cslua_gettop(lua_State *L);
void cslua_settop(lua_State *L, int idx);
void cslua_rotate(lua_State *L, int idx, int n);
void cslua_copy(lua_State *L, int fromidx, int toidx);
int cslua_type(lua_State *L, int idx);
const char *cslua_typename(lua_State *L, int tp);
int cslua_equal(lua_State *L, int idx1, int idx2);
int cslua_rawequal(lua_State *L, int idx1, int idx2);
int cslua_lessthan(lua_State *L, int idx1, int idx2);
lua_Number cslua_tonumberx(lua_State *L, int idx, int *isnum);
lua_Integer cslua_tointegerx(lua_State *L, int idx, int *isnum);
size_t cslua_objlen(lua_State *L, int idx);
