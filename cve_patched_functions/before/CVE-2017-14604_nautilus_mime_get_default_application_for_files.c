nautilus_mime_get_default_application_for_files (GList *files)
{
    GList *l, *sorted_files;
    NautilusFile *file;
    GAppInfo *app, *one_app;

    g_assert (files != NULL);

    sorted_files = g_list_sort (g_list_copy (files), (GCompareFunc) file_compare_by_mime_type);

    app = NULL;
    for (l = sorted_files; l != NULL; l = l->next)
    {
        file = l->data;

        if (l->prev &&
            file_compare_by_mime_type (file, l->prev->data) == 0 &&
            file_compare_by_parent_uri (file, l->prev->data) == 0)
        {
            continue;
        }

        one_app = nautilus_mime_get_default_application_for_file (file);
        if (one_app == NULL || (app != NULL && !g_app_info_equal (app, one_app)))
        {
            if (app)
            {
                g_object_unref (app);
            }
            if (one_app)
            {
                g_object_unref (one_app);
            }
            app = NULL;
            break;
        }

        if (app == NULL)
        {
            app = one_app;
        }
        else
        {
            g_object_unref (one_app);
        }
    }

    g_list_free (sorted_files);

    return app;
}
