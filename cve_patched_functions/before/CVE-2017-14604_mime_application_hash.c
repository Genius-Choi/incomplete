mime_application_hash (GAppInfo *app)
{
    const char *id;

    id = g_app_info_get_id (app);

    if (id == NULL)
    {
        return GPOINTER_TO_UINT (app);
    }

    return g_str_hash (id);
}
