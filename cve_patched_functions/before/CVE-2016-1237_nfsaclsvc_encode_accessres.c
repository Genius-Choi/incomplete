static int nfsaclsvc_encode_accessres(struct svc_rqst *rqstp, __be32 *p,
		struct nfsd3_accessres *resp)
{
	p = nfs2svc_encode_fattr(rqstp, p, &resp->fh, &resp->stat);
	*p++ = htonl(resp->access);
	return xdr_ressize_check(rqstp, p);
}
