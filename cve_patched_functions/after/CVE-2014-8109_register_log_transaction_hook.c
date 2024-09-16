static const char *register_log_transaction_hook(cmd_parms *cmd, void *_cfg,
                                                const char *file,
                                                const char *function)
{
    return register_named_file_function_hook("log_transaction", cmd, _cfg,
                                             file, function, APR_HOOK_FIRST);
}
