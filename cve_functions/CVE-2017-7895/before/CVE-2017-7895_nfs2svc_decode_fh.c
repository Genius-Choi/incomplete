__be32 *nfs2svc_decode_fh(__be32 *p, struct svc_fh *fhp)
{
	return decode_fh(p, fhp);
}
