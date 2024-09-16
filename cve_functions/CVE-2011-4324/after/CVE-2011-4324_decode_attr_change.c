static int decode_attr_change(struct xdr_stream *xdr, uint32_t *bitmap, uint64_t *change)
{
	__be32 *p;

	*change = 0;
	if (unlikely(bitmap[0] & (FATTR4_WORD0_CHANGE - 1U)))
		return -EIO;
	if (likely(bitmap[0] & FATTR4_WORD0_CHANGE)) {
		READ_BUF(8);
		READ64(*change);
		bitmap[0] &= ~FATTR4_WORD0_CHANGE;
	}
	dprintk("%s: change attribute=%Lu\n", __func__,
			(unsigned long long)*change);
	return 0;
}
