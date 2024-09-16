iakerb_initiator_step(iakerb_ctx_id_t ctx,
                      krb5_gss_cred_id_t cred,
                      krb5_gss_name_t name,
                      OM_uint32 time_req,
                      const gss_buffer_t input_token,
                      gss_buffer_t output_token)
{
    krb5_error_code code = 0;
    krb5_data in = empty_data(), out = empty_data(), realm = empty_data();
    krb5_data *cookie = NULL;
    OM_uint32 tmp;
    unsigned int flags = 0;
    krb5_ticket_times times;

    output_token->length = 0;
    output_token->value = NULL;

    if (input_token != GSS_C_NO_BUFFER) {
        code = iakerb_parse_token(ctx, 0, input_token, NULL, &cookie, &in);
        if (code != 0)
            goto cleanup;

        code = iakerb_save_token(ctx, input_token);
        if (code != 0)
            goto cleanup;
    }

    switch (ctx->state) {
    case IAKERB_AS_REQ:
        if (ctx->icc == NULL) {
            code = iakerb_init_creds_ctx(ctx, cred, time_req);
            if (code != 0)
                goto cleanup;
        }

        code = krb5_init_creds_step(ctx->k5c, ctx->icc, &in, &out, &realm,
                                    &flags);
        if (code != 0) {
            if (cred->have_tgt) {
                /* We were trying to refresh; keep going with current creds. */
                ctx->state = IAKERB_TGS_REQ;
                krb5_clear_error_message(ctx->k5c);
            } else {
                goto cleanup;
            }
        } else if (!(flags & KRB5_INIT_CREDS_STEP_FLAG_CONTINUE)) {
            krb5_init_creds_get_times(ctx->k5c, ctx->icc, &times);
            kg_cred_set_initial_refresh(ctx->k5c, cred, &times);
            cred->expire = times.endtime;

            krb5_init_creds_free(ctx->k5c, ctx->icc);
            ctx->icc = NULL;

            ctx->state = IAKERB_TGS_REQ;
        } else
            break;
        in = empty_data();
        /* Done with AS request; fall through to TGS request. */
    case IAKERB_TGS_REQ:
        if (ctx->tcc == NULL) {
            code = iakerb_tkt_creds_ctx(ctx, cred, name, time_req);
            if (code != 0)
                goto cleanup;
        }

        code = krb5_tkt_creds_step(ctx->k5c, ctx->tcc, &in, &out, &realm,
                                   &flags);
        if (code != 0)
            goto cleanup;
        if (!(flags & KRB5_TKT_CREDS_STEP_FLAG_CONTINUE)) {
            krb5_tkt_creds_get_times(ctx->k5c, ctx->tcc, &times);
            cred->expire = times.endtime;

            krb5_tkt_creds_free(ctx->k5c, ctx->tcc);
            ctx->tcc = NULL;

            ctx->state = IAKERB_AP_REQ;
        } else
            break;
        /* Done with TGS request; fall through to AP request. */
    case IAKERB_AP_REQ:
        break;
    }

    if (out.length != 0) {
        assert(ctx->state != IAKERB_AP_REQ);

        code = iakerb_make_token(ctx, &realm, cookie, &out,
                                 (input_token == GSS_C_NO_BUFFER),
                                 output_token);
        if (code != 0)
            goto cleanup;

        /* Save the token for generating a future checksum */
        code = iakerb_save_token(ctx, output_token);
        if (code != 0)
            goto cleanup;

        ctx->count++;
    }

cleanup:
    if (code != 0)
        gss_release_buffer(&tmp, output_token);
    krb5_free_data(ctx->k5c, cookie);
    krb5_free_data_contents(ctx->k5c, &out);
    krb5_free_data_contents(ctx->k5c, &realm);

    return code;
}
