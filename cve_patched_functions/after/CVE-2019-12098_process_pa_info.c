process_pa_info(krb5_context context,
		const krb5_principal client,
		const AS_REQ *asreq,
		struct pa_info_data *paid,
		METHOD_DATA *md)
{
    struct pa_info_data *p = NULL;
    size_t i;

    for (i = 0; p == NULL && i < sizeof(pa_prefs)/sizeof(pa_prefs[0]); i++) {
	PA_DATA *pa = find_pa_data(md, pa_prefs[i].type);
	if (pa == NULL)
	    continue;
	paid->salt.salttype = (krb5_salttype)pa_prefs[i].type;
	p = (*pa_prefs[i].salt_info)(context, client, asreq,
				     paid, &pa->padata_value);
    }
    return p;
}
