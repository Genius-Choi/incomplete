static const char *register_quick_block(cmd_parms *cmd, void *_cfg,
                                        const char *line)
{
    return register_named_block_function_hook("quick", cmd, _cfg,
                                              line);
}
