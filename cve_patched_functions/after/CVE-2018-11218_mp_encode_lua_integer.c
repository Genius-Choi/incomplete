void mp_encode_lua_integer(lua_State *L, mp_buf *buf) {
#if (LUA_VERSION_NUM < 503) && BITS_32
    lua_Number i = lua_tonumber(L,-1);
#else
    lua_Integer i = lua_tointeger(L,-1);
#endif
    mp_encode_int(L, buf, (int64_t)i);
}
