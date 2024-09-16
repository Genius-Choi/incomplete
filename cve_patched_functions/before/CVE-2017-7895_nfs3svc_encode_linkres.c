nfs3svc_encode_linkres(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_linkres *resp)
{
	p = encode_post_op_attr(rqstp, p, &resp->fh);
	p = encode_wcc_data(rqstp, p, &resp->tfh);
	return xdr_ressize_check(rqstp, p);
}
