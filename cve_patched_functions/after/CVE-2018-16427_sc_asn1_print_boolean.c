static void sc_asn1_print_boolean(const u8 * buf, size_t buflen)
{
	if (!buflen)
		return;

	if (buf[0])
		printf("true");
	else
		printf("false");
}
