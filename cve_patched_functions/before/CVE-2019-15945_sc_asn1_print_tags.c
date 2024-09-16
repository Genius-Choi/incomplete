void sc_asn1_print_tags(const u8 * buf, size_t buflen)
{
	print_tags_recursive(buf, buf, buflen, 0);
}
