application_launch_parameters_free (ApplicationLaunchParameters *parameters)
{
    g_object_unref (parameters->application);
    g_list_free_full (parameters->uris, g_free);

    g_free (parameters);
}
