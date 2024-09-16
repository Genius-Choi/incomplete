nfsd4_decode_time(struct nfsd4_compoundargs *argp, struct timespec *tv)
{
	DECODE_HEAD;
	u64 sec;

	READ_BUF(12);
	p = xdr_decode_hyper(p, &sec);
	tv->tv_sec = sec;
	tv->tv_nsec = be32_to_cpup(p++);
	if (tv->tv_nsec >= (u32)1000000000)
		return nfserr_inval;

	DECODE_TAIL;
}
