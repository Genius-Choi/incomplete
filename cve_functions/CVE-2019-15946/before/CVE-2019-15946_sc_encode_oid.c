sc_encode_oid (struct sc_context *ctx, struct sc_object_id *id,
		unsigned char **out, size_t *size)
{
	static const struct sc_asn1_entry c_asn1_object_id[2] = {
		{ "oid", SC_ASN1_OBJECT, SC_ASN1_TAG_OBJECT, SC_ASN1_ALLOC, NULL, NULL },
		{ NULL, 0, 0, 0, NULL, NULL }
	};
	struct sc_asn1_entry asn1_object_id[2];
	int rv;

	sc_copy_asn1_entry(c_asn1_object_id, asn1_object_id);
	sc_format_asn1_entry(asn1_object_id + 0, id, NULL, 1);

	rv = _sc_asn1_encode(ctx, asn1_object_id, out, size, 1);
	LOG_TEST_RET(ctx, rv, "Cannot encode object ID");

	return SC_SUCCESS;
}
