deep_count_got_info (GObject      *source_object,
                     GAsyncResult *res,
                     gpointer      user_data)
{
    GFileInfo *info;
    const char *id;
    GFile *file = (GFile *) source_object;
    DeepCountState *state = (DeepCountState *) user_data;

    info = g_file_query_info_finish (file, res, NULL);
    if (info != NULL)
    {
        id = g_file_info_get_attribute_string (info, G_FILE_ATTRIBUTE_ID_FILESYSTEM);
        state->fs_id = g_strdup (id);
        g_object_unref (info);
    }
    deep_count_load (state, file);
}
