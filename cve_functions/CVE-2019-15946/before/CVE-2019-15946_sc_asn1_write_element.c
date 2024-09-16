int sc_asn1_write_element(sc_context_t *ctx, unsigned int tag,
	const u8 * data, size_t datalen, u8 ** out, size_t * outlen)
{
	return asn1_write_element(ctx, tag, data, datalen, out, outlen);
}
