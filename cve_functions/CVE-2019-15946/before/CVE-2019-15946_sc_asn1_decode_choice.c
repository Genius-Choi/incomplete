int sc_asn1_decode_choice(sc_context_t *ctx, struct sc_asn1_entry *asn1,
			  const u8 *in, size_t len, const u8 **newp, size_t *len_left)
{
	return asn1_decode(ctx, asn1, in, len, newp, len_left, 1, 0);
}
