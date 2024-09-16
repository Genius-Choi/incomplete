static const char *register_quick_hook(cmd_parms *cmd, void *_cfg,
                                       const char *file, const char *function)
{
    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIRECTORY|NOT_IN_FILES|
                                                NOT_IN_HTACCESS);
    if (err) {
        return err;
    }
    return register_named_file_function_hook("quick", cmd, _cfg, file,
                                             function, APR_HOOK_MIDDLE);
}
