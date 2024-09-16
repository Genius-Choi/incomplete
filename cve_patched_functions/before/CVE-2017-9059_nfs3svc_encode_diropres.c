nfs3svc_encode_diropres(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_diropres *resp)
{
	if (resp->status == 0) {
		p = encode_fh(p, &resp->fh);
		p = encode_post_op_attr(rqstp, p, &resp->fh);
	}
	p = encode_post_op_attr(rqstp, p, &resp->dirfh);
	return xdr_ressize_check(rqstp, p);
}
