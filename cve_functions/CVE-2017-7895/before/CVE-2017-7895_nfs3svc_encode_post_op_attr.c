nfs3svc_encode_post_op_attr(struct svc_rqst *rqstp, __be32 *p, struct svc_fh *fhp)
{
	return encode_post_op_attr(rqstp, p, fhp);
}
