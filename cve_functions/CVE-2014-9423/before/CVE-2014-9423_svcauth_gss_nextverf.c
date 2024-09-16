svcauth_gss_nextverf(struct svc_req *rqst, u_int num)
{
	struct svc_rpc_gss_data	*gd;
	gss_buffer_desc		 signbuf;
	OM_uint32		 maj_stat, min_stat;

	log_debug("in svcauth_gss_nextverf()");

	if (rqst->rq_xprt->xp_auth == NULL)
		return (FALSE);

	gd = SVCAUTH_PRIVATE(rqst->rq_xprt->xp_auth);

	gss_release_buffer(&min_stat, &gd->checksum);

	signbuf.value = &num;
	signbuf.length = sizeof(num);

	maj_stat = gss_get_mic(&min_stat, gd->ctx, gd->sec.qop,
			       &signbuf, &gd->checksum);

	if (maj_stat != GSS_S_COMPLETE) {
		log_status("gss_get_mic", maj_stat, min_stat);
		return (FALSE);
	}
	rqst->rq_xprt->xp_verf.oa_flavor = RPCSEC_GSS;
	rqst->rq_xprt->xp_verf.oa_base = (caddr_t)gd->checksum.value;
	rqst->rq_xprt->xp_verf.oa_length = (u_int)gd->checksum.length;

	return (TRUE);
}
