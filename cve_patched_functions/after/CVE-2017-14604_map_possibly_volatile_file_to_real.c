map_possibly_volatile_file_to_real (GFile         *volatile_file,
                                    GCancellable  *cancellable,
                                    GError       **error)
{
    GFile *real_file = NULL;
    GFileInfo *info = NULL;

    info = g_file_query_info (volatile_file,
                              G_FILE_ATTRIBUTE_STANDARD_IS_SYMLINK ","
                              G_FILE_ATTRIBUTE_STANDARD_IS_VOLATILE ","
                              G_FILE_ATTRIBUTE_STANDARD_SYMLINK_TARGET,
                              G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
                              cancellable,
                              error);
    if (info == NULL)
    {
        return NULL;
    }
    else
    {
        gboolean is_volatile;

        is_volatile = g_file_info_get_attribute_boolean (info,
                                                         G_FILE_ATTRIBUTE_STANDARD_IS_VOLATILE);
        if (is_volatile)
        {
            const gchar *target;

            target = g_file_info_get_symlink_target (info);
            real_file = g_file_resolve_relative_path (volatile_file, target);
        }
    }

    g_object_unref (info);

    if (real_file == NULL)
    {
        real_file = g_object_ref (volatile_file);
    }

    return real_file;
}
