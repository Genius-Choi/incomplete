static void *create_dir_config(apr_pool_t *p, char *dir)
{
    ap_lua_dir_cfg *cfg = apr_pcalloc(p, sizeof(ap_lua_dir_cfg));
    cfg->package_paths = apr_array_make(p, 2, sizeof(char *));
    cfg->package_cpaths = apr_array_make(p, 2, sizeof(char *));
    cfg->mapped_handlers =
        apr_array_make(p, 1, sizeof(ap_lua_mapped_handler_spec *));
    cfg->mapped_filters =
        apr_array_make(p, 1, sizeof(ap_lua_filter_handler_spec *));
    cfg->pool = p;
    cfg->hooks = apr_hash_make(p);
    cfg->dir = apr_pstrdup(p, dir);
    cfg->vm_scope = AP_LUA_SCOPE_UNSET;
    cfg->codecache = AP_LUA_CACHE_UNSET;
    cfg->vm_min = 0;
    cfg->vm_max = 0;

    return cfg;
}
