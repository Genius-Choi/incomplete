nfsd4_decode_readdir(struct nfsd4_compoundargs *argp, struct nfsd4_readdir *readdir)
{
	DECODE_HEAD;

	READ_BUF(24);
	p = xdr_decode_hyper(p, &readdir->rd_cookie);
	COPYMEM(readdir->rd_verf.data, sizeof(readdir->rd_verf.data));
	readdir->rd_dircount = be32_to_cpup(p++);
	readdir->rd_maxcount = be32_to_cpup(p++);
	if ((status = nfsd4_decode_bitmap(argp, readdir->rd_bmval)))
		goto out;

	DECODE_TAIL;
}
