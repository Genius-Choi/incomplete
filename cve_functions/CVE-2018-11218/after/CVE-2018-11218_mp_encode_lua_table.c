void mp_encode_lua_table(lua_State *L, mp_buf *buf, int level) {
    if (table_is_an_array(L))
        mp_encode_lua_table_as_array(L,buf,level);
    else
        mp_encode_lua_table_as_map(L,buf,level);
}
