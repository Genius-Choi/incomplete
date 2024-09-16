nfssvc_release_fhandle(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd_fhandle *resp)
{
	fh_put(&resp->fh);
	return 1;
}
