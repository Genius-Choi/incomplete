static void *create_server_config(apr_pool_t *p, server_rec *s)
{

    ap_lua_server_cfg *cfg = apr_pcalloc(p, sizeof(ap_lua_server_cfg));
    cfg->vm_reslists = apr_hash_make(p);
    apr_thread_rwlock_create(&cfg->vm_reslists_lock, p);
    cfg->root_path = NULL;

    return cfg;
}
