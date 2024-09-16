nfsd4_decode_sequence(struct nfsd4_compoundargs *argp,
		      struct nfsd4_sequence *seq)
{
	DECODE_HEAD;

	READ_BUF(NFS4_MAX_SESSIONID_LEN + 16);
	COPYMEM(seq->sessionid.data, NFS4_MAX_SESSIONID_LEN);
	seq->seqid = be32_to_cpup(p++);
	seq->slotid = be32_to_cpup(p++);
	seq->maxslots = be32_to_cpup(p++);
	seq->cachethis = be32_to_cpup(p++);

	DECODE_TAIL;
}
