test_dir_is_parent (GFile *child,
                    GFile *root)
{
    GFile *f, *tmp;

    f = g_file_dup (child);
    while (f)
    {
        if (g_file_equal (f, root))
        {
            g_object_unref (f);
            return TRUE;
        }
        tmp = f;
        f = g_file_get_parent (f);
        g_object_unref (tmp);
    }
    if (f)
    {
        g_object_unref (f);
    }
    return FALSE;
}
