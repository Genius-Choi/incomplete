nfs4_preprocess_seqid_op(struct nfsd4_compound_state *cstate, u32 seqid,
			 stateid_t *stateid, char typemask,
			 struct nfs4_ol_stateid **stpp,
			 struct nfsd_net *nn)
{
	__be32 status;
	struct nfs4_stid *s;
	struct nfs4_ol_stateid *stp = NULL;

	dprintk("NFSD: %s: seqid=%d stateid = " STATEID_FMT "\n", __func__,
		seqid, STATEID_VAL(stateid));

	*stpp = NULL;
	status = nfsd4_lookup_stateid(cstate, stateid, typemask, &s, nn);
	if (status)
		return status;
	stp = openlockstateid(s);
	nfsd4_cstate_assign_replay(cstate, stp->st_stateowner);

	status = nfs4_seqid_op_checks(cstate, stateid, seqid, stp);
	if (!status)
		*stpp = stp;
	else
		nfs4_put_stid(&stp->st_stid);
	return status;
}
