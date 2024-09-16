int sc_asn1_encode(sc_context_t *ctx, const struct sc_asn1_entry *asn1,
		   u8 **ptr, size_t *size)
{
	return asn1_encode(ctx, asn1, ptr, size, 0);
}
