void mp_encode_lua_bool(lua_State *L, mp_buf *buf) {
    unsigned char b = lua_toboolean(L,-1) ? 0xc3 : 0xc2;
    mp_buf_append(L,buf,&b,1);
}
