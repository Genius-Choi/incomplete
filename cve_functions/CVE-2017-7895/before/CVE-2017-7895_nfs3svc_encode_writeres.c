nfs3svc_encode_writeres(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_writeres *resp)
{
	struct nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);

	p = encode_wcc_data(rqstp, p, &resp->fh);
	if (resp->status == 0) {
		*p++ = htonl(resp->count);
		*p++ = htonl(resp->committed);
		*p++ = htonl(nn->nfssvc_boot.tv_sec);
		*p++ = htonl(nn->nfssvc_boot.tv_usec);
	}
	return xdr_ressize_check(rqstp, p);
}
