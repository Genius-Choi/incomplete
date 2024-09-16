make_activation_parameters (GList  *uris,
                            GList **unhandled_uris)
{
    GList *ret, *l, *app_uris;
    NautilusFile *file;
    GAppInfo *app, *old_app;
    GHashTable *app_table;
    char *uri;

    ret = NULL;
    *unhandled_uris = NULL;

    app_table = g_hash_table_new_full
                    ((GHashFunc) mime_application_hash,
                    (GEqualFunc) g_app_info_equal,
                    (GDestroyNotify) g_object_unref,
                    (GDestroyNotify) g_list_free);

    for (l = uris; l != NULL; l = l->next)
    {
        uri = l->data;
        file = nautilus_file_get_by_uri (uri);

        app = nautilus_mime_get_default_application_for_file (file);
        if (app != NULL)
        {
            app_uris = NULL;

            if (g_hash_table_lookup_extended (app_table, app,
                                              (gpointer *) &old_app,
                                              (gpointer *) &app_uris))
            {
                g_hash_table_steal (app_table, old_app);

                app_uris = g_list_prepend (app_uris, uri);

                g_object_unref (app);
                app = old_app;
            }
            else
            {
                app_uris = g_list_prepend (NULL, uri);
            }

            g_hash_table_insert (app_table, app, app_uris);
        }
        else
        {
            *unhandled_uris = g_list_prepend (*unhandled_uris, uri);
        }
        nautilus_file_unref (file);
    }

    g_hash_table_foreach (app_table,
                          (GHFunc) list_to_parameters_foreach,
                          &ret);

    g_hash_table_destroy (app_table);

    *unhandled_uris = g_list_reverse (*unhandled_uris);

    return g_list_reverse (ret);
}
