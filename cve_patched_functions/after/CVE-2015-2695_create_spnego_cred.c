create_spnego_cred(OM_uint32 *minor_status, gss_cred_id_t mcred,
		   spnego_gss_cred_id_t *cred_out)
{
	spnego_gss_cred_id_t spcred;

	*cred_out = NULL;
	spcred = calloc(1, sizeof(spnego_gss_cred_id_rec));
	if (spcred == NULL) {
		*minor_status = ENOMEM;
		return GSS_S_FAILURE;
	}
	spcred->mcred = mcred;
	*cred_out = spcred;
	return GSS_S_COMPLETE;
}
