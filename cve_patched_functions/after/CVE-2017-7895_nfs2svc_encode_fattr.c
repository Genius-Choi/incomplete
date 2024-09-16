__be32 *nfs2svc_encode_fattr(struct svc_rqst *rqstp, __be32 *p, struct svc_fh *fhp, struct kstat *stat)
{
	return encode_fattr(rqstp, p, fhp, stat);
}
