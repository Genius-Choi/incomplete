nfsd4_decode_lockt(struct nfsd4_compoundargs *argp, struct nfsd4_lockt *lockt)
{
	DECODE_HEAD;
		        
	READ_BUF(32);
	lockt->lt_type = be32_to_cpup(p++);
	if((lockt->lt_type < NFS4_READ_LT) || (lockt->lt_type > NFS4_WRITEW_LT))
		goto xdr_error;
	p = xdr_decode_hyper(p, &lockt->lt_offset);
	p = xdr_decode_hyper(p, &lockt->lt_length);
	COPYMEM(&lockt->lt_clientid, 8);
	lockt->lt_owner.len = be32_to_cpup(p++);
	READ_BUF(lockt->lt_owner.len);
	READMEM(lockt->lt_owner.data, lockt->lt_owner.len);

	DECODE_TAIL;
}
