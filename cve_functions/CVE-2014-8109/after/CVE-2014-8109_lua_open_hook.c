static int lua_open_hook(lua_State *L, apr_pool_t *p)
{
    lua_open_callback(L, p, NULL);
    return OK;
}
