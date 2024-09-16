void sc_format_asn1_entry(struct sc_asn1_entry *entry, void *parm, void *arg,
			  int set_present)
{
	entry->parm = parm;
	entry->arg  = arg;
	if (set_present)
		entry->flags |= SC_ASN1_PRESENT;
}
