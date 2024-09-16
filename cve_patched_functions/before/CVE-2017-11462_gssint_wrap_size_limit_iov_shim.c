gssint_wrap_size_limit_iov_shim(gss_mechanism mech,
                                OM_uint32 *minor_status,
                                gss_ctx_id_t context_handle,
                                int conf_req_flag,
                                gss_qop_t qop_req,
                                OM_uint32 req_output_size,
                                OM_uint32 *max_input_size)
{
    gss_iov_buffer_desc iov[4];
    OM_uint32           status;
    OM_uint32           ohlen;

    iov[0].type = GSS_IOV_BUFFER_TYPE_HEADER;
    iov[0].buffer.value = NULL;
    iov[0].buffer.length = 0;

    iov[1].type = GSS_IOV_BUFFER_TYPE_DATA;
    iov[1].buffer.length = req_output_size;
    iov[1].buffer.value = NULL;

    iov[2].type = GSS_IOV_BUFFER_TYPE_PADDING;
    iov[2].buffer.value = NULL;
    iov[2].buffer.length = 0;

    iov[3].type = GSS_IOV_BUFFER_TYPE_TRAILER;
    iov[3].buffer.value = NULL;
    iov[3].buffer.length = 0;

    assert(mech->gss_wrap_iov_length);

    status = mech->gss_wrap_iov_length(minor_status, context_handle,
                                       conf_req_flag, qop_req,
                                       NULL, iov,
                                       sizeof(iov)/sizeof(iov[0]));
    if (status != GSS_S_COMPLETE) {
        map_error(minor_status, mech);
        return status;
    }

    ohlen = iov[0].buffer.length + iov[3].buffer.length;

    if (iov[2].buffer.length == 0 && ohlen < req_output_size)
        *max_input_size = req_output_size - ohlen;
    else
        *max_input_size = 0;

    return GSS_S_COMPLETE;
}
