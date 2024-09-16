static kadm5_ret_t new_server_handle(krb5_ui_4 api_version,
                                     struct svc_req *rqstp,
                                     kadm5_server_handle_t
                                     *out_handle)
{
    kadm5_server_handle_t handle;

    *out_handle = NULL;

    if (! (handle = (kadm5_server_handle_t)
           malloc(sizeof(*handle))))
        return ENOMEM;

    *handle = *(kadm5_server_handle_t)global_server_handle;
    handle->api_version = api_version;

    if (! gss_to_krb5_name(handle, rqst2name(rqstp),
                           &handle->current_caller)) {
        free(handle);
        return KADM5_FAILURE;
    }

    *out_handle = handle;
    return 0;
}
