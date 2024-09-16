iakerb_get_initial_state(iakerb_ctx_id_t ctx,
                         krb5_gss_cred_id_t cred,
                         krb5_gss_name_t target,
                         OM_uint32 time_req,
                         enum iakerb_state *state)
{
    krb5_creds in_creds, *out_creds = NULL;
    krb5_error_code code;

    memset(&in_creds, 0, sizeof(in_creds));

    in_creds.client = cred->name->princ;
    in_creds.server = target->princ;

    if (cred->name->ad_context != NULL) {
        code = krb5_authdata_export_authdata(ctx->k5c,
                                             cred->name->ad_context,
                                             AD_USAGE_TGS_REQ,
                                             &in_creds.authdata);
        if (code != 0)
            goto cleanup;
    }

    if (time_req != 0 && time_req != GSS_C_INDEFINITE) {
        krb5_timestamp now;

        code = krb5_timeofday(ctx->k5c, &now);
        if (code != 0)
            goto cleanup;

        in_creds.times.endtime = now + time_req;
    }

    /* Make an AS request if we have no creds or it's time to refresh them. */
    if (cred->expire == 0 || kg_cred_time_to_refresh(ctx->k5c, cred)) {
        *state = IAKERB_AS_REQ;
        code = 0;
        goto cleanup;
    }

    code = krb5_get_credentials(ctx->k5c, KRB5_GC_CACHED, cred->ccache,
                                &in_creds, &out_creds);
    if (code == KRB5_CC_NOTFOUND || code == KRB5_CC_NOT_KTYPE) {
        *state = cred->have_tgt ? IAKERB_TGS_REQ : IAKERB_AS_REQ;
        code = 0;
    } else if (code == 0) {
        *state = IAKERB_AP_REQ;
        krb5_free_creds(ctx->k5c, out_creds);
    }

cleanup:
    krb5_free_authdata(ctx->k5c, in_creds.authdata);

    return code;
}
