// Autogenerated by gameplay-luagen
#ifndef LUA_TILESET_H_
#define LUA_TILESET_H_

namespace gameplay
{

// Lua bindings for TileSet.
int lua_TileSet__gc(lua_State* state);
int lua_TileSet_addRef(lua_State* state);
int lua_TileSet_draw(lua_State* state);
int lua_TileSet_getColor(lua_State* state);
int lua_TileSet_getColumnCount(lua_State* state);
int lua_TileSet_getHeight(lua_State* state);
int lua_TileSet_getNode(lua_State* state);
int lua_TileSet_getOpacity(lua_State* state);
int lua_TileSet_getRefCount(lua_State* state);
int lua_TileSet_getRowCount(lua_State* state);
int lua_TileSet_getTileHeight(lua_State* state);
int lua_TileSet_getTileSource(lua_State* state);
int lua_TileSet_getTileWidth(lua_State* state);
int lua_TileSet_getWidth(lua_State* state);
int lua_TileSet_release(lua_State* state);
int lua_TileSet_setColor(lua_State* state);
int lua_TileSet_setOpacity(lua_State* state);
int lua_TileSet_setTileSource(lua_State* state);
int lua_TileSet_static_create(lua_State* state);

void luaRegister_TileSet();

}

#endif
