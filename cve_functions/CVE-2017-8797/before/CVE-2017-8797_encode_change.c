static __be32 *encode_change(__be32 *p, struct kstat *stat, struct inode *inode,
			     struct svc_export *exp)
{
	if (exp->ex_flags & NFSEXP_V4ROOT) {
		*p++ = cpu_to_be32(convert_to_wallclock(exp->cd->flush_time));
		*p++ = 0;
	} else if (IS_I_VERSION(inode)) {
		p = xdr_encode_hyper(p, inode->i_version);
	} else {
		*p++ = cpu_to_be32(stat->ctime.tv_sec);
		*p++ = cpu_to_be32(stat->ctime.tv_nsec);
	}
	return p;
}
