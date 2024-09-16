nfs3svc_release_fhandle(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_attrstat *resp)
{
	fh_put(&resp->fh);
	return 1;
}
