static const char *register_map_to_storage_block(cmd_parms *cmd, void *_cfg,
                                                 const char *line)
{
    return register_named_block_function_hook("map_to_storage", cmd, _cfg,
                                              line);
}
