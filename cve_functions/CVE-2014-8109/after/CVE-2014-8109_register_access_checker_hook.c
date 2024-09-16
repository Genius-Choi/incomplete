static const char *register_access_checker_hook(cmd_parms *cmd, void *_cfg,
                                                const char *file,
                                                const char *function,
                                                const char *when)
{
    int apr_hook_when = APR_HOOK_MIDDLE;

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

    return register_named_file_function_hook("access_checker", cmd, _cfg,
                                             file, function, apr_hook_when);
}
