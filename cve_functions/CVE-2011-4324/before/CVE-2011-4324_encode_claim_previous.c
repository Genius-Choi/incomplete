static inline void encode_claim_previous(struct xdr_stream *xdr, fmode_t type)
{
	__be32 *p;

	RESERVE_SPACE(4);
	WRITE32(NFS4_OPEN_CLAIM_PREVIOUS);
	encode_delegation_type(xdr, type);
}
