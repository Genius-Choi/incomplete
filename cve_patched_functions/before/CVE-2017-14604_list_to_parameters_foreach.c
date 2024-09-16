list_to_parameters_foreach (GAppInfo  *application,
                            GList     *uris,
                            GList    **ret)
{
    ApplicationLaunchParameters *parameters;

    uris = g_list_reverse (uris);

    parameters = application_launch_parameters_new
                     (application, uris);
    *ret = g_list_prepend (*ret, parameters);
}
