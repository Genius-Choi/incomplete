krb5_gss_verify_mic(minor_status, context_handle,
                    message_buffer, token_buffer,
                    qop_state)
    OM_uint32           *minor_status;
    gss_ctx_id_t        context_handle;
    gss_buffer_t        message_buffer;
    gss_buffer_t        token_buffer;
    gss_qop_t           *qop_state;
{
    OM_uint32           rstat;

    rstat = kg_unseal(minor_status, context_handle,
                      token_buffer, message_buffer,
                      NULL, qop_state, KG_TOK_MIC_MSG);
    return(rstat);
}
