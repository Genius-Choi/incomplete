nfs4_preprocess_stateid_op(struct svc_rqst *rqstp,
		struct nfsd4_compound_state *cstate, struct svc_fh *fhp,
		stateid_t *stateid, int flags, struct file **filpp, bool *tmp_file)
{
	struct inode *ino = d_inode(fhp->fh_dentry);
	struct net *net = SVC_NET(rqstp);
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);
	struct nfs4_stid *s = NULL;
	__be32 status;

	if (filpp)
		*filpp = NULL;
	if (tmp_file)
		*tmp_file = false;

	if (grace_disallows_io(net, ino))
		return nfserr_grace;

	if (ZERO_STATEID(stateid) || ONE_STATEID(stateid)) {
		status = check_special_stateids(net, fhp, stateid, flags);
		goto done;
	}

	status = nfsd4_lookup_stateid(cstate, stateid,
				NFS4_DELEG_STID|NFS4_OPEN_STID|NFS4_LOCK_STID,
				&s, nn);
	if (status)
		return status;
	status = check_stateid_generation(stateid, &s->sc_stateid,
			nfsd4_has_session(cstate));
	if (status)
		goto out;

	switch (s->sc_type) {
	case NFS4_DELEG_STID:
		status = nfs4_check_delegmode(delegstateid(s), flags);
		break;
	case NFS4_OPEN_STID:
	case NFS4_LOCK_STID:
		status = nfs4_check_olstateid(fhp, openlockstateid(s), flags);
		break;
	default:
		status = nfserr_bad_stateid;
		break;
	}
	if (status)
		goto out;
	status = nfs4_check_fh(fhp, s);

done:
	if (!status && filpp)
		status = nfs4_check_file(rqstp, fhp, s, filpp, tmp_file, flags);
out:
	if (s)
		nfs4_put_stid(s);
	return status;
}
