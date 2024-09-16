void mp_encode_lua_number(lua_State *L, mp_buf *buf) {
    lua_Number n = lua_tonumber(L,-1);

    if (IS_INT64_EQUIVALENT(n)) {
        mp_encode_lua_integer(L, buf);
    } else {
        mp_encode_double(L,buf,(double)n);
    }
}
