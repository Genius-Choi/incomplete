skip_file (CommonJob *common,
           GFile     *file)
{
    if (common->skip_files == NULL)
    {
        common->skip_files =
            g_hash_table_new_full (g_file_hash, (GEqualFunc) g_file_equal, g_object_unref, NULL);
    }

    g_hash_table_insert (common->skip_files, g_object_ref (file), file);
}
