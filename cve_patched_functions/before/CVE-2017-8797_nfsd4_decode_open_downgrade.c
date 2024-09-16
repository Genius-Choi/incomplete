nfsd4_decode_open_downgrade(struct nfsd4_compoundargs *argp, struct nfsd4_open_downgrade *open_down)
{
	DECODE_HEAD;
		    
	status = nfsd4_decode_stateid(argp, &open_down->od_stateid);
	if (status)
		return status;
	READ_BUF(4);
	open_down->od_seqid = be32_to_cpup(p++);
	status = nfsd4_decode_share_access(argp, &open_down->od_share_access,
					   &open_down->od_deleg_want, NULL);
	if (status)
		return status;
	status = nfsd4_decode_share_deny(argp, &open_down->od_share_deny);
	if (status)
		return status;
	DECODE_TAIL;
}
