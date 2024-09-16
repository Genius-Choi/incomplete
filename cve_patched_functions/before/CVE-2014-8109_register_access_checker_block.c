static const char *register_access_checker_block(cmd_parms *cmd, void *_cfg,
                                                 const char *line)
{

    return register_named_block_function_hook("access_checker", cmd, _cfg,
                                              line);
}
