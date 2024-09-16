file_compare_by_mime_type (NautilusFile *file_a,
                           NautilusFile *file_b)
{
    char *mime_type_a, *mime_type_b;
    int ret;

    mime_type_a = nautilus_file_get_mime_type (file_a);
    mime_type_b = nautilus_file_get_mime_type (file_b);

    ret = strcmp (mime_type_a, mime_type_b);

    g_free (mime_type_a);
    g_free (mime_type_b);

    return ret;
}
