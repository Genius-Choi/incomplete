static const char *register_package_helper(cmd_parms *cmd, 
                                           const char *arg,
                                           apr_array_header_t *dir_array)
{
    apr_status_t rv;

    ap_lua_server_cfg *server_cfg =
        ap_get_module_config(cmd->server->module_config, &lua_module);

    char *fixed_filename;
    rv = apr_filepath_merge(&fixed_filename, 
                            server_cfg->root_path, 
                            arg,
                            APR_FILEPATH_NOTRELATIVE, 
                            cmd->pool);

    if (rv != APR_SUCCESS) {
        return apr_psprintf(cmd->pool,
                            "Unable to build full path to file, %s", arg);
    }

    *(const char **) apr_array_push(dir_array) = fixed_filename;
    return NULL;
}
