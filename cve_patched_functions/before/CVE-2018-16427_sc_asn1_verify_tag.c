const u8 *sc_asn1_verify_tag(sc_context_t *ctx, const u8 * buf, size_t buflen,
			     unsigned int tag_in, size_t *taglen_out)
{
	return sc_asn1_skip_tag(ctx, &buf, &buflen, tag_in, taglen_out);
}
