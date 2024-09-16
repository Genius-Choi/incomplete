static const char *register_translate_name_hook(cmd_parms *cmd, void *_cfg,
                                                const char *file,
                                                const char *function,
                                                const char *when)
{
    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIRECTORY|NOT_IN_FILES|
                                           NOT_IN_HTACCESS);
    int apr_hook_when = APR_HOOK_MIDDLE;
    if (err) {
        return err;
    }
    
    if (when) { 
        if (!strcasecmp(when, "early")) { 
            apr_hook_when = AP_LUA_HOOK_FIRST;
        } 
        else if (!strcasecmp(when, "late")) { 
            apr_hook_when = AP_LUA_HOOK_LAST;
        } 
        else { 
            return "Third argument must be 'early' or 'late'";
        }
    }

    return register_named_file_function_hook("translate_name", cmd, _cfg,
                                             file, function, apr_hook_when);
}
