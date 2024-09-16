nfs3svc_encode_attrstat(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_attrstat *resp)
{
	if (resp->status == 0) {
		lease_get_mtime(d_inode(resp->fh.fh_dentry),
				&resp->stat.mtime);
		p = encode_fattr3(rqstp, p, &resp->fh, &resp->stat);
	}
	return xdr_ressize_check(rqstp, p);
}
