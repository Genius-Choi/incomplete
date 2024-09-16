static void sc_asn1_print_object_id(const u8 * buf, size_t buflen)
{
	struct sc_object_id oid;
	const char *sbuf;

	if (sc_asn1_decode_object_id(buf, buflen, &oid)) {
		printf("decode error");
		return;
	}

	sbuf = sc_dump_oid(&oid);
	printf(" %s", sbuf);
	openssl_print_object_sn(sbuf);
}
