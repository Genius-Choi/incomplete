nfs3svc_encode_renameres(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_renameres *resp)
{
	p = encode_wcc_data(rqstp, p, &resp->ffh);
	p = encode_wcc_data(rqstp, p, &resp->tfh);
	return xdr_ressize_check(rqstp, p);
}
