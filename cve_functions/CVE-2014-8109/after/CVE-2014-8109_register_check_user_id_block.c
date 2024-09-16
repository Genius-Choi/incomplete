static const char *register_check_user_id_block(cmd_parms *cmd, void *_cfg,
                                                const char *line)
{
    return register_named_block_function_hook("check_user_id", cmd, _cfg,
                                              line);
}
