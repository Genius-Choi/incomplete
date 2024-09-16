file_compare_by_parent_uri (NautilusFile *file_a,
                            NautilusFile *file_b)
{
    char *parent_uri_a, *parent_uri_b;
    int ret;

    parent_uri_a = nautilus_file_get_parent_uri (file_a);
    parent_uri_b = nautilus_file_get_parent_uri (file_b);

    ret = strcmp (parent_uri_a, parent_uri_b);

    g_free (parent_uri_a);
    g_free (parent_uri_b);

    return ret;
}
