_krb5_pk_set_user_id(krb5_context context,
		     krb5_principal principal,
		     krb5_pk_init_ctx ctx,
		     struct hx509_certs_data *certs)
{
    hx509_certs c = hx509_certs_ref(certs);
    hx509_query *q = NULL;
    int ret;

    if (ctx->id->certs)
	hx509_certs_free(&ctx->id->certs);
    if (ctx->id->cert) {
	hx509_cert_free(ctx->id->cert);
	ctx->id->cert = NULL;
    }

    ctx->id->certs = c;
    ctx->anonymous = 0;

    ret = hx509_query_alloc(context->hx509ctx, &q);
    if (ret) {
	pk_copy_error(context, context->hx509ctx, ret,
		      "Allocate query to find signing certificate");
	return ret;
    }

    hx509_query_match_option(q, HX509_QUERY_OPTION_PRIVATE_KEY);
    hx509_query_match_option(q, HX509_QUERY_OPTION_KU_DIGITALSIGNATURE);

    if (principal && strncmp("LKDC:SHA1.", krb5_principal_get_realm(context, principal), 9) == 0) {
	ctx->id->flags |= PKINIT_BTMM;
    }

    ret = find_cert(context, ctx->id, q, &ctx->id->cert);
    hx509_query_free(context->hx509ctx, q);

    if (ret == 0 && _krb5_have_debug(context, 2)) {
	hx509_name name;
	char *str, *sn;
	heim_integer i;

	ret = hx509_cert_get_subject(ctx->id->cert, &name);
	if (ret)
	    goto out;

	ret = hx509_name_to_string(name, &str);
	hx509_name_free(&name);
	if (ret)
	    goto out;

	ret = hx509_cert_get_serialnumber(ctx->id->cert, &i);
	if (ret) {
	    free(str);
	    goto out;
	}

	ret = der_print_hex_heim_integer(&i, &sn);
	der_free_heim_integer(&i);
	if (ret) {
	    free(name);
	    goto out;
	}

	_krb5_debug(context, 2, "using cert: subject: %s sn: %s", str, sn);
	free(str);
	free(sn);
    }
 out:

    return ret;
}
