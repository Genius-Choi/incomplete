static const char *register_fixups_block(cmd_parms *cmd, void *_cfg,
                                         const char *line)
{
    return register_named_block_function_hook("fixups", cmd, _cfg, line);
}
