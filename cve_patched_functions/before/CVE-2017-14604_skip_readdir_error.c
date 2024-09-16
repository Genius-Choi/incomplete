skip_readdir_error (CommonJob *common,
                    GFile     *dir)
{
    if (common->skip_readdir_error == NULL)
    {
        common->skip_readdir_error =
            g_hash_table_new_full (g_file_hash, (GEqualFunc) g_file_equal, g_object_unref, NULL);
    }

    g_hash_table_insert (common->skip_readdir_error, g_object_ref (dir), dir);
}
