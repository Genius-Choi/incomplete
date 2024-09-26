kg_unseal_stream_iov(OM_uint32 *minor_status,
                     krb5_gss_ctx_id_rec *ctx,
                     int *conf_state,
                     gss_qop_t *qop_state,
                     gss_iov_buffer_desc *iov,
                     int iov_count,
                     int toktype)
{
    unsigned char *ptr;
    unsigned int bodysize;
    OM_uint32 code = 0, major_status = GSS_S_FAILURE;
    krb5_context context = ctx->k5_context;
    int conf_req_flag, toktype2;
    int i = 0, j;
    gss_iov_buffer_desc *tiov = NULL;
    gss_iov_buffer_t stream, data = NULL;
    gss_iov_buffer_t theader, tdata = NULL, tpadding, ttrailer;

    assert(toktype == KG_TOK_WRAP_MSG);

    if (toktype != KG_TOK_WRAP_MSG || (ctx->gss_flags & GSS_C_DCE_STYLE)) {
        code = EINVAL;
        goto cleanup;
    }

    stream = kg_locate_iov(iov, iov_count, GSS_IOV_BUFFER_TYPE_STREAM);
    assert(stream != NULL);

    ptr = (unsigned char *)stream->buffer.value;

    code = g_verify_token_header(ctx->mech_used,
                                 &bodysize, &ptr, -1,
                                 stream->buffer.length, 0);
    if (code != 0) {
        major_status = GSS_S_DEFECTIVE_TOKEN;
        goto cleanup;
    }

    if (bodysize < 2) {
        *minor_status = (OM_uint32)G_BAD_TOK_HEADER;
        return GSS_S_DEFECTIVE_TOKEN;
    }

    toktype2 = load_16_be(ptr);

    ptr += 2;
    bodysize -= 2;

    tiov = (gss_iov_buffer_desc *)calloc((size_t)iov_count + 2, sizeof(gss_iov_buffer_desc));
    if (tiov == NULL) {
        code = ENOMEM;
        goto cleanup;
    }

    /* HEADER */
    theader = &tiov[i++];
    theader->type = GSS_IOV_BUFFER_TYPE_HEADER;
    theader->buffer.value = stream->buffer.value;
    theader->buffer.length = ptr - (unsigned char *)stream->buffer.value;
    if (bodysize < 14 ||
        stream->buffer.length != theader->buffer.length + bodysize) {
        major_status = GSS_S_DEFECTIVE_TOKEN;
        goto cleanup;
    }
    theader->buffer.length += 14;

    /* n[SIGN_DATA] | DATA | m[SIGN_DATA] */
    for (j = 0; j < iov_count; j++) {
        OM_uint32 type = GSS_IOV_BUFFER_TYPE(iov[j].type);

        if (type == GSS_IOV_BUFFER_TYPE_DATA) {
            if (data != NULL) {
                /* only a single DATA buffer can appear */
                code = EINVAL;
                goto cleanup;
            }

            data = &iov[j];
            tdata = &tiov[i];
        }
        if (type == GSS_IOV_BUFFER_TYPE_DATA ||
            type == GSS_IOV_BUFFER_TYPE_SIGN_ONLY)
            tiov[i++] = iov[j];
    }

    if (data == NULL) {
        /* a single DATA buffer must be present */
        code = EINVAL;
        goto cleanup;
    }

    /* PADDING | TRAILER */
    tpadding = &tiov[i++];
    tpadding->type = GSS_IOV_BUFFER_TYPE_PADDING;
    tpadding->buffer.length = 0;
    tpadding->buffer.value = NULL;

    ttrailer = &tiov[i++];
    ttrailer->type = GSS_IOV_BUFFER_TYPE_TRAILER;

    switch (toktype2) {
    case KG2_TOK_MIC_MSG:
    case KG2_TOK_WRAP_MSG:
    case KG2_TOK_DEL_CTX: {
        size_t ec, rrc;
        krb5_enctype enctype;
        unsigned int k5_headerlen = 0;
        unsigned int k5_trailerlen = 0;

        if (ctx->have_acceptor_subkey)
            enctype = ctx->acceptor_subkey->keyblock.enctype;
        else
            enctype = ctx->subkey->keyblock.enctype;
        conf_req_flag = ((ptr[0] & FLAG_WRAP_CONFIDENTIAL) != 0);
        ec = conf_req_flag ? load_16_be(ptr + 2) : 0;
        rrc = load_16_be(ptr + 4);

        if (rrc != 0) {
            if (!gss_krb5int_rotate_left((unsigned char *)stream->buffer.value + 16,
                                         stream->buffer.length - 16, rrc)) {
                code = ENOMEM;
                goto cleanup;
            }
            store_16_be(0, ptr + 4); /* set RRC to zero */
        }

        if (conf_req_flag) {
            code = krb5_c_crypto_length(context, enctype, KRB5_CRYPTO_TYPE_HEADER, &k5_headerlen);
            if (code != 0)
                goto cleanup;
            theader->buffer.length += k5_headerlen; /* length validated later */
        }

        /* no PADDING for CFX, EC is used instead */
        code = krb5_c_crypto_length(context, enctype,
                                    conf_req_flag ? KRB5_CRYPTO_TYPE_TRAILER : KRB5_CRYPTO_TYPE_CHECKSUM,
                                    &k5_trailerlen);
        if (code != 0)
            goto cleanup;

        ttrailer->buffer.length = ec + (conf_req_flag ? 16 : 0 /* E(Header) */) + k5_trailerlen;
        ttrailer->buffer.value = (unsigned char *)stream->buffer.value +
            stream->buffer.length - ttrailer->buffer.length;
        break;
    }
    case KG_TOK_MIC_MSG:
    case KG_TOK_WRAP_MSG:
    case KG_TOK_DEL_CTX:
        theader->buffer.length += ctx->cksum_size +
            kg_confounder_size(context, ctx->enc->keyblock.enctype);

        /*
         * we can't set the padding accurately until decryption;
         * kg_fixup_padding_iov() will take care of this
         */
        tpadding->buffer.length = 1;
        tpadding->buffer.value = (unsigned char *)stream->buffer.value + stream->buffer.length - 1;

        /* no TRAILER for pre-CFX */
        ttrailer->buffer.length = 0;
        ttrailer->buffer.value = NULL;

        break;
    default:
        code = (OM_uint32)G_BAD_TOK_HEADER;
        major_status = GSS_S_DEFECTIVE_TOKEN;
        goto cleanup;
        break;
    }

    /* IOV: -----------0-------------+---1---+--2--+----------------3--------------*/
    /* Old: GSS-Header | Conf        | Data  | Pad |                               */
    /* CFX: GSS-Header | Kerb-Header | Data  |     | EC | E(Header) | Kerb-Trailer */
    /* GSS: -------GSS-HEADER--------+-DATA--+-PAD-+----------GSS-TRAILER----------*/

    /* validate lengths */
    if (stream->buffer.length < theader->buffer.length +
        tpadding->buffer.length +
        ttrailer->buffer.length)
    {
        code = (OM_uint32)KRB5_BAD_MSIZE;
        major_status = GSS_S_DEFECTIVE_TOKEN;
        goto cleanup;
    }

    /* setup data */
    tdata->buffer.length = stream->buffer.length - ttrailer->buffer.length -
        tpadding->buffer.length - theader->buffer.length;

    assert(data != NULL);

    if (data->type & GSS_IOV_BUFFER_FLAG_ALLOCATE) {
        code = kg_allocate_iov(tdata, tdata->buffer.length);
        if (code != 0)
            goto cleanup;
        memcpy(tdata->buffer.value,
               (unsigned char *)stream->buffer.value + theader->buffer.length, tdata->buffer.length);
    } else
        tdata->buffer.value = (unsigned char *)stream->buffer.value + theader->buffer.length;

    assert(i <= iov_count + 2);

    major_status = kg_unseal_iov_token(&code, ctx, conf_state, qop_state,
                                       tiov, i, toktype);
    if (major_status == GSS_S_COMPLETE)
        *data = *tdata;
    else
        kg_release_iov(tdata, 1);

cleanup:
    if (tiov != NULL)
        free(tiov);

    *minor_status = code;

    return major_status;
}
