static int asn1_decode_se_info(sc_context_t *ctx, const u8 *obj, size_t objlen,
			       sc_pkcs15_sec_env_info_t ***se, size_t *num, int depth)
{
	struct sc_pkcs15_sec_env_info **ses;
	const unsigned char *ptr = obj;
	size_t idx, ptrlen = objlen;
	int ret;

	ses = calloc(SC_MAX_SE_NUM, sizeof(sc_pkcs15_sec_env_info_t *));
	if (ses == NULL)
		return SC_ERROR_OUT_OF_MEMORY;

	for (idx=0; idx < SC_MAX_SE_NUM && ptrlen; )   {
		struct sc_asn1_entry asn1_se[2];
		struct sc_asn1_entry asn1_se_info[4];
		struct sc_pkcs15_sec_env_info si;

		sc_copy_asn1_entry(c_asn1_se, asn1_se);
		sc_copy_asn1_entry(c_asn1_se_info, asn1_se_info);

		si.aid.len = sizeof(si.aid.value);
		sc_format_asn1_entry(asn1_se_info + 0, &si.se, NULL, 0);
		sc_format_asn1_entry(asn1_se_info + 1, &si.owner, NULL, 0);
		sc_format_asn1_entry(asn1_se_info + 2, &si.aid.value, &si.aid.len, 0);
		sc_format_asn1_entry(asn1_se + 0, asn1_se_info, NULL, 0);

		ret = asn1_decode(ctx, asn1_se, ptr, ptrlen, &ptr, &ptrlen, 0, depth+1);
		if (ret != SC_SUCCESS)
			goto err;
		if (!(asn1_se_info[1].flags & SC_ASN1_PRESENT))
			sc_init_oid(&si.owner);

		ses[idx] = calloc(1, sizeof(sc_pkcs15_sec_env_info_t));
		if (ses[idx] == NULL) {
			ret = SC_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy(ses[idx], &si, sizeof(struct sc_pkcs15_sec_env_info));
		idx++;
	}

	*se  = ses;
	*num = idx;
	ret = SC_SUCCESS;
err:
	if (ret != SC_SUCCESS) {
		size_t i;
		for (i = 0; i < idx; i++)
			if (ses[i])
				free(ses[i]);
		free(ses);
	}

	return ret;
}
