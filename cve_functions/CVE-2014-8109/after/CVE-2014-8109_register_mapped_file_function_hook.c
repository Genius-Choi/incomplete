static const char *register_mapped_file_function_hook(const char *pattern,
                                                     cmd_parms *cmd,
                                                     void *_cfg,
                                                     const char *file,
                                                     const char *function)
{
    ap_lua_mapped_handler_spec *spec;
    ap_lua_dir_cfg *cfg = (ap_lua_dir_cfg *) _cfg;
    ap_regex_t *regex = apr_pcalloc(cmd->pool, sizeof(ap_regex_t));
    if (ap_regcomp(regex, pattern,0)) {
        return "Invalid regex pattern!";
    }

    spec = apr_pcalloc(cmd->pool, sizeof(ap_lua_mapped_handler_spec));
    spec->file_name = apr_pstrdup(cmd->pool, file);
    spec->function_name = apr_pstrdup(cmd->pool, function);
    spec->scope = cfg->vm_scope;
    spec->uri_pattern = regex;

    *(ap_lua_mapped_handler_spec **) apr_array_push(cfg->mapped_handlers) = spec;
    return NULL;
}
