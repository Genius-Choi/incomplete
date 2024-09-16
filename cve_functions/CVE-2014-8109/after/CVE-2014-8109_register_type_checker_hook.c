static const char *register_type_checker_hook(cmd_parms *cmd, void *_cfg,
                                              const char *file,
                                              const char *function)
{
    return register_named_file_function_hook("type_checker", cmd, _cfg, file,
                                             function, APR_HOOK_MIDDLE);
}
