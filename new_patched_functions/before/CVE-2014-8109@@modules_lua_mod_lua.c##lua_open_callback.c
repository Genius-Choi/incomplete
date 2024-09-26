static void lua_open_callback(lua_State *L, apr_pool_t *p, void *ctx)
{
    ap_lua_init(L, p);
    ap_lua_load_apache2_lmodule(L);
    ap_lua_load_request_lmodule(L, p);
    ap_lua_load_config_lmodule(L);
}
