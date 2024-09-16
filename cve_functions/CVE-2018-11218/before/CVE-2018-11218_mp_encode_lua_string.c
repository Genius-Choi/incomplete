void mp_encode_lua_string(lua_State *L, mp_buf *buf) {
    size_t len;
    const char *s;

    s = lua_tolstring(L,-1,&len);
    mp_encode_bytes(L,buf,(const unsigned char*)s,len);
}
