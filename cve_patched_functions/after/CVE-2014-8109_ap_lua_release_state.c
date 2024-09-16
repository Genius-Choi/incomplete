static void ap_lua_release_state(lua_State* L, ap_lua_vm_spec* spec, request_rec* r) {
    char *hash;
    apr_reslist_t* reslist = NULL;
    if (spec->scope == AP_LUA_SCOPE_SERVER) {
        ap_lua_server_spec* sspec = NULL;
        lua_settop(L, 0);
        lua_getfield(L, LUA_REGISTRYINDEX, "Apache2.Lua.server_spec");
        sspec = (ap_lua_server_spec*) lua_touserdata(L, 1);
        hash = apr_psprintf(r->pool, "reslist:%s", spec->file);
        if (apr_pool_userdata_get((void **)&reslist, hash,
                                r->server->process->pool) == APR_SUCCESS) {
            AP_DEBUG_ASSERT(sspec != NULL);
            if (reslist != NULL) {
                apr_reslist_release(reslist, sspec);
            }
        }
    }
}
