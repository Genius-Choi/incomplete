static ap_lua_vm_spec *create_vm_spec(apr_pool_t **lifecycle_pool,
                                      request_rec *r,
                                      const ap_lua_dir_cfg *cfg,
                                      const ap_lua_server_cfg *server_cfg,
                                      const char *filename,
                                      const char *bytecode,
                                      apr_size_t bytecode_len,
                                      const char *function,
                                      const char *what)
{
    apr_pool_t *pool;
    ap_lua_vm_spec *spec = apr_pcalloc(r->pool, sizeof(ap_lua_vm_spec));

    spec->scope = cfg->vm_scope;
    spec->pool = r->pool;
    spec->package_paths = cfg->package_paths;
    spec->package_cpaths = cfg->package_cpaths;
    spec->cb = &lua_open_callback;
    spec->cb_arg = NULL;
    spec->bytecode = bytecode;
    spec->bytecode_len = bytecode_len;
    spec->codecache = (cfg->codecache == AP_LUA_CACHE_UNSET) ? AP_LUA_CACHE_STAT : cfg->codecache;
    spec->vm_min = cfg->vm_min ? cfg->vm_min : 1;
    spec->vm_max = cfg->vm_max ? cfg->vm_max : 1;
    
    if (filename) {
        char *file;
        apr_filepath_merge(&file, server_cfg->root_path,
                           filename, APR_FILEPATH_NOTRELATIVE, r->pool);
        spec->file = file;
    }
    else {
        spec->file = r->filename;
    }
    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r, APLOGNO(02313)
                  "%s details: scope: %s, file: %s, func: %s",
                  what, scope_to_string(spec->scope), spec->file,
                  function ? function : "-");

    switch (spec->scope) {
    case AP_LUA_SCOPE_ONCE:
    case AP_LUA_SCOPE_UNSET:
        apr_pool_create(&pool, r->pool);
        break;
    case AP_LUA_SCOPE_REQUEST:
        pool = r->pool;
        break;
    case AP_LUA_SCOPE_CONN:
        pool = r->connection->pool;
        break;
#if APR_HAS_THREADS
    case AP_LUA_SCOPE_THREAD:
        pool = apr_thread_pool_get(r->connection->current_thread);
        break;
    case AP_LUA_SCOPE_SERVER:
        pool = r->server->process->pool;
        break;
#endif
    default:
        ap_assert(0);
    }

    *lifecycle_pool = pool;
    return spec;
}
