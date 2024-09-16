krb5_init_creds_store(krb5_context context,
		      krb5_init_creds_context ctx,
		      krb5_ccache id)
{
    krb5_error_code ret;

    if (ctx->cred.client == NULL) {
	ret = KRB5KDC_ERR_PREAUTH_REQUIRED;
	krb5_set_error_message(context, ret, "init creds not completed yet");
	return ret;
    }

    ret = krb5_cc_initialize(context, id, ctx->cred.client);
    if (ret)
	return ret;

    ret = krb5_cc_store_cred(context, id, &ctx->cred);
    if (ret)
	return ret;

    if (ctx->cred.flags.b.enc_pa_rep) {
	krb5_data data = { 3, rk_UNCONST("yes") };
	ret = krb5_cc_set_config(context, id, ctx->cred.server,
				 "fast_avail", &data);
	if (ret)
	    return ret;
    }

    return ret;
}
