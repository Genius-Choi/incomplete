static int ldump_writer(lua_State *L, const void *b, size_t size, void *B)
{
    (void) L;
    luaL_addlstring((luaL_Buffer *) B, (const char *) b, size);
    return 0;
}
