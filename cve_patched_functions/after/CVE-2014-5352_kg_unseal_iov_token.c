kg_unseal_iov_token(OM_uint32 *minor_status,
                    krb5_gss_ctx_id_rec *ctx,
                    int *conf_state,
                    gss_qop_t *qop_state,
                    gss_iov_buffer_desc *iov,
                    int iov_count,
                    int toktype)
{
    krb5_error_code code;
    krb5_context context = ctx->k5_context;
    unsigned char *ptr;
    gss_iov_buffer_t header;
    gss_iov_buffer_t padding;
    gss_iov_buffer_t trailer;
    size_t input_length;
    unsigned int bodysize;
    int toktype2;

    header = kg_locate_header_iov(iov, iov_count, toktype);
    if (header == NULL) {
        *minor_status = EINVAL;
        return GSS_S_FAILURE;
    }

    padding = kg_locate_iov(iov, iov_count, GSS_IOV_BUFFER_TYPE_PADDING);
    trailer = kg_locate_iov(iov, iov_count, GSS_IOV_BUFFER_TYPE_TRAILER);

    ptr = (unsigned char *)header->buffer.value;
    input_length = header->buffer.length;

    if ((ctx->gss_flags & GSS_C_DCE_STYLE) == 0 &&
        toktype == KG_TOK_WRAP_MSG) {
        size_t data_length, assoc_data_length;

        kg_iov_msglen(iov, iov_count, &data_length, &assoc_data_length);

        input_length += data_length - assoc_data_length;

        if (padding != NULL)
            input_length += padding->buffer.length;

        if (trailer != NULL)
            input_length += trailer->buffer.length;
    }

    code = g_verify_token_header(ctx->mech_used,
                                 &bodysize, &ptr, -1,
                                 input_length, 0);
    if (code != 0) {
        *minor_status = code;
        return GSS_S_DEFECTIVE_TOKEN;
    }

    if (bodysize < 2) {
        *minor_status = (OM_uint32)G_BAD_TOK_HEADER;
        return GSS_S_DEFECTIVE_TOKEN;
    }

    toktype2 = load_16_be(ptr);

    ptr += 2;
    bodysize -= 2;

    switch (toktype2) {
    case KG2_TOK_MIC_MSG:
    case KG2_TOK_WRAP_MSG:
    case KG2_TOK_DEL_CTX:
        code = gss_krb5int_unseal_v3_iov(context, minor_status, ctx, iov, iov_count,
                                         conf_state, qop_state, toktype);
        break;
    case KG_TOK_MIC_MSG:
    case KG_TOK_WRAP_MSG:
    case KG_TOK_DEL_CTX:
        code = kg_unseal_v1_iov(context, minor_status, ctx, iov, iov_count,
                                (size_t)(ptr - (unsigned char *)header->buffer.value),
                                conf_state, qop_state, toktype);
        break;
    default:
        *minor_status = (OM_uint32)G_BAD_TOK_HEADER;
        code = GSS_S_DEFECTIVE_TOKEN;
        break;
    }

    if (code != 0)
        save_error_info(*minor_status, context);

    return code;
}
