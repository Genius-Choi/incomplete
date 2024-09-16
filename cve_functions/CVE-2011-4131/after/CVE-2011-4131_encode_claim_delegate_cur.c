static inline void encode_claim_delegate_cur(struct xdr_stream *xdr, const struct qstr *name, const nfs4_stateid *stateid)
{
	__be32 *p;

	p = reserve_space(xdr, 4+NFS4_STATEID_SIZE);
	*p++ = cpu_to_be32(NFS4_OPEN_CLAIM_DELEGATE_CUR);
	xdr_encode_opaque_fixed(p, stateid->data, NFS4_STATEID_SIZE);
	encode_string(xdr, name->len, name->name);
}
