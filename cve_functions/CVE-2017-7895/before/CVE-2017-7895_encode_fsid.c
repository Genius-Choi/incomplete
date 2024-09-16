static __be32 *encode_fsid(__be32 *p, struct svc_fh *fhp)
{
	u64 f;
	switch(fsid_source(fhp)) {
	default:
	case FSIDSOURCE_DEV:
		p = xdr_encode_hyper(p, (u64)huge_encode_dev
				     (fhp->fh_dentry->d_sb->s_dev));
		break;
	case FSIDSOURCE_FSID:
		p = xdr_encode_hyper(p, (u64) fhp->fh_export->ex_fsid);
		break;
	case FSIDSOURCE_UUID:
		f = ((u64*)fhp->fh_export->ex_uuid)[0];
		f ^= ((u64*)fhp->fh_export->ex_uuid)[1];
		p = xdr_encode_hyper(p, f);
		break;
	}
	return p;
}
