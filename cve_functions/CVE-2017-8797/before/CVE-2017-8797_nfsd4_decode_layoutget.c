nfsd4_decode_layoutget(struct nfsd4_compoundargs *argp,
		struct nfsd4_layoutget *lgp)
{
	DECODE_HEAD;

	READ_BUF(36);
	lgp->lg_signal = be32_to_cpup(p++);
	lgp->lg_layout_type = be32_to_cpup(p++);
	lgp->lg_seg.iomode = be32_to_cpup(p++);
	p = xdr_decode_hyper(p, &lgp->lg_seg.offset);
	p = xdr_decode_hyper(p, &lgp->lg_seg.length);
	p = xdr_decode_hyper(p, &lgp->lg_minlength);

	status = nfsd4_decode_stateid(argp, &lgp->lg_sid);
	if (status)
		return status;

	READ_BUF(4);
	lgp->lg_maxcount = be32_to_cpup(p++);

	DECODE_TAIL;
}
