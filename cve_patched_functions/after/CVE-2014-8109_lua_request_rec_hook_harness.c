static int lua_request_rec_hook_harness(request_rec *r, const char *name, int apr_hook_when)
{
    int rc;
    apr_pool_t *pool;
    lua_State *L;
    ap_lua_vm_spec *spec;
    ap_lua_server_cfg *server_cfg = ap_get_module_config(r->server->module_config,
                                                         &lua_module);
    const ap_lua_dir_cfg *cfg = ap_get_module_config(r->per_dir_config,
                                                     &lua_module);
    const char *key = apr_psprintf(r->pool, "%s_%d", name, apr_hook_when);
    apr_array_header_t *hook_specs = apr_hash_get(cfg->hooks, key,
                                                  APR_HASH_KEY_STRING);
    if (hook_specs) {
        int i;
        for (i = 0; i < hook_specs->nelts; i++) {
            ap_lua_mapped_handler_spec *hook_spec =
                ((ap_lua_mapped_handler_spec **) hook_specs->elts)[i];

            if (hook_spec == NULL) {
                continue;
            }
            spec = create_vm_spec(&pool, r, cfg, server_cfg,
                                  hook_spec->file_name,
                                  hook_spec->bytecode,
                                  hook_spec->bytecode_len,
                                  hook_spec->function_name,
                                  "request hook");

            L = ap_lua_get_lua_state(pool, spec, r);

            if (!L) {
                ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01477)
                    "lua: Failed to obtain lua interpreter for entry function '%s' in %s",
                              hook_spec->function_name, hook_spec->file_name);
                return HTTP_INTERNAL_SERVER_ERROR;
            }

            if (hook_spec->function_name != NULL) {
                lua_getglobal(L, hook_spec->function_name);
                if (!lua_isfunction(L, -1)) {
                    ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, APLOGNO(01478)
                               "lua: Unable to find entry function '%s' in %s (not a valid function)",
                                  hook_spec->function_name,
                                  hook_spec->file_name);
                    ap_lua_release_state(L, spec, r);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }

                ap_lua_run_lua_request(L, r);
            }
            else {
                int t;
                ap_lua_run_lua_request(L, r);

                t = lua_gettop(L);
                lua_setglobal(L, "r");
                lua_settop(L, t);
            }

            if (lua_pcall(L, 1, 1, 0)) {
                report_lua_error(L, r);
                ap_lua_release_state(L, spec, r);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
            rc = DECLINED;
            if (lua_isnumber(L, -1)) {
                rc = lua_tointeger(L, -1);
                ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r, "Lua hook %s:%s for phase %s returned %d", 
                              hook_spec->file_name, hook_spec->function_name, name, rc);
            }
            else { 
                ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r, "Lua hook %s:%s for phase %s did not return a numeric value", 
                              hook_spec->file_name, hook_spec->function_name, name);
                return HTTP_INTERNAL_SERVER_ERROR;
            }
            if (rc != DECLINED) {
                ap_lua_release_state(L, spec, r);
                return rc;
            }
            ap_lua_release_state(L, spec, r);
        }
    }
    return DECLINED;
}
