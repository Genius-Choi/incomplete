application_launch_parameters_new (GAppInfo *application,
                                   GList    *uris)
{
    ApplicationLaunchParameters *result;

    result = g_new0 (ApplicationLaunchParameters, 1);
    result->application = g_object_ref (application);
    result->uris = g_list_copy_deep (uris, (GCopyFunc) g_strdup, NULL);

    return result;
}
