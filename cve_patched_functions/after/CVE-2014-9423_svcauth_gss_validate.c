svcauth_gss_validate(struct svc_req *rqst, struct svc_rpc_gss_data *gd, struct rpc_msg *msg)
{
	struct opaque_auth	*oa;
	gss_buffer_desc		 rpcbuf, checksum;
	OM_uint32		 maj_stat, min_stat, qop_state;
	u_char			 rpchdr[128];
	int32_t			*buf;

	log_debug("in svcauth_gss_validate()");

	memset(rpchdr, 0, sizeof(rpchdr));

	/* XXX - Reconstruct RPC header for signing (from xdr_callmsg). */
	oa = &msg->rm_call.cb_cred;
	if (oa->oa_length > MAX_AUTH_BYTES)
		return (FALSE);

	/* 8 XDR units from the IXDR macro calls. */
	if (sizeof(rpchdr) < (8 * BYTES_PER_XDR_UNIT +
			      RNDUP(oa->oa_length)))
		return (FALSE);

	buf = (int32_t *)(void *)rpchdr;
	IXDR_PUT_LONG(buf, msg->rm_xid);
	IXDR_PUT_ENUM(buf, msg->rm_direction);
	IXDR_PUT_LONG(buf, msg->rm_call.cb_rpcvers);
	IXDR_PUT_LONG(buf, msg->rm_call.cb_prog);
	IXDR_PUT_LONG(buf, msg->rm_call.cb_vers);
	IXDR_PUT_LONG(buf, msg->rm_call.cb_proc);
	IXDR_PUT_ENUM(buf, oa->oa_flavor);
	IXDR_PUT_LONG(buf, oa->oa_length);
	if (oa->oa_length) {
		memcpy((caddr_t)buf, oa->oa_base, oa->oa_length);
		buf += RNDUP(oa->oa_length) / sizeof(int32_t);
	}
	rpcbuf.value = rpchdr;
	rpcbuf.length = (u_char *)buf - rpchdr;

	checksum.value = msg->rm_call.cb_verf.oa_base;
	checksum.length = msg->rm_call.cb_verf.oa_length;

	maj_stat = gss_verify_mic(&min_stat, gd->ctx, &rpcbuf, &checksum,
				  &qop_state);

	if (maj_stat != GSS_S_COMPLETE) {
		log_status("gss_verify_mic", maj_stat, min_stat);
		if (log_badverf != NULL)
			(*log_badverf)(gd->client_name,
			       svcauth_gss_name,
			       rqst, msg, log_badverf_data);
		return (FALSE);
	}
	return (TRUE);
}
