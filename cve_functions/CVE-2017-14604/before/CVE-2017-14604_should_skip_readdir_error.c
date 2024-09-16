should_skip_readdir_error (CommonJob *common,
                           GFile     *dir)
{
    if (common->skip_readdir_error != NULL)
    {
        return g_hash_table_lookup (common->skip_readdir_error, dir) != NULL;
    }
    return FALSE;
}
