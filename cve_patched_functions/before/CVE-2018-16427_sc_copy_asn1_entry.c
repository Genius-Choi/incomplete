void sc_copy_asn1_entry(const struct sc_asn1_entry *src,
			struct sc_asn1_entry *dest)
{
	while (src->name != NULL) {
		*dest = *src;
		dest++;
		src++;
	}
	dest->name = NULL;
}
