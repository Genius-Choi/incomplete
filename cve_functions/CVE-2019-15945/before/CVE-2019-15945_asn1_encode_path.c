static int asn1_encode_path(sc_context_t *ctx, const sc_path_t *path,
			    u8 **buf, size_t *bufsize, int depth, unsigned int parent_flags)
{
	int r;
 	struct sc_asn1_entry asn1_path[5];
	sc_path_t tpath = *path;

	sc_copy_asn1_entry(c_asn1_path, asn1_path);
	sc_format_asn1_entry(asn1_path + 0, (void *) &tpath.value, (void *) &tpath.len, 1);

	asn1_path[0].flags |= parent_flags;
	if (path->count > 0) {
		sc_format_asn1_entry(asn1_path + 1, (void *) &tpath.index, NULL, 1);
		sc_format_asn1_entry(asn1_path + 2, (void *) &tpath.count, NULL, 1);
	}
	r = asn1_encode(ctx, asn1_path, buf, bufsize, depth + 1);
	return r;
}
