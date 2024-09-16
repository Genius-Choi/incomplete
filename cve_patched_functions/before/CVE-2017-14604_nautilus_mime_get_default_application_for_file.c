nautilus_mime_get_default_application_for_file (NautilusFile *file)
{
    GAppInfo *app;
    char *mime_type;
    char *uri_scheme;

    if (!nautilus_mime_actions_check_if_required_attributes_ready (file))
    {
        return NULL;
    }

    mime_type = nautilus_file_get_mime_type (file);
    app = g_app_info_get_default_for_type (mime_type,
                                           !nautilus_file_is_local_or_fuse (file));
    g_free (mime_type);

    if (app == NULL)
    {
        uri_scheme = nautilus_file_get_uri_scheme (file);
        if (uri_scheme != NULL)
        {
            app = g_app_info_get_default_for_uri_scheme (uri_scheme);
            g_free (uri_scheme);
        }
    }

    return app;
}
