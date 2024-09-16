_sc_asn1_decode(sc_context_t *ctx, struct sc_asn1_entry *asn1,
		       const u8 *in, size_t len, const u8 **newp, size_t *left,
		       int choice, int depth)
{
	return asn1_decode(ctx, asn1, in, len, newp, left, choice, depth);
}
