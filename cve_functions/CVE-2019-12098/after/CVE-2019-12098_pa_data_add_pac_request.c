pa_data_add_pac_request(krb5_context context,
			krb5_get_init_creds_ctx *ctx,
			METHOD_DATA *md)
{
    size_t len = 0, length;
    krb5_error_code ret;
    PA_PAC_REQUEST req;
    void *buf;

    switch (ctx->req_pac) {
    case KRB5_INIT_CREDS_TRISTATE_UNSET:
	return 0; /* don't bother */
    case KRB5_INIT_CREDS_TRISTATE_TRUE:
	req.include_pac = 1;
	break;
    case KRB5_INIT_CREDS_TRISTATE_FALSE:
	req.include_pac = 0;
    }

    ASN1_MALLOC_ENCODE(PA_PAC_REQUEST, buf, length,
		       &req, &len, ret);
    if (ret)
	return ret;
    if(len != length)
	krb5_abortx(context, "internal error in ASN.1 encoder");

    ret = krb5_padata_add(context, md, KRB5_PADATA_PA_PAC_REQUEST, buf, len);
    if (ret)
	free(buf);

    return 0;
}
