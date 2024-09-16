static const char *register_authz_provider(cmd_parms *cmd, void *_cfg,
                                           const char *name, const char *file,
                                           const char *function)
{
    lua_authz_provider_spec *spec;
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (err)
        return err;

    spec = apr_pcalloc(cmd->pool, sizeof(*spec));
    spec->name = name;
    spec->file_name = file;
    spec->function_name = function;

    apr_hash_set(lua_authz_providers, name, APR_HASH_KEY_STRING, spec);
    ap_register_auth_provider(cmd->pool, AUTHZ_PROVIDER_GROUP, name,
                              AUTHZ_PROVIDER_VERSION,
                              &lua_authz_provider,
                              AP_AUTH_INTERNAL_PER_CONF);
    return NULL;
}
