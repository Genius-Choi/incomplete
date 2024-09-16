static struct sock *llc_lookup_listener(struct llc_sap *sap,
					struct llc_addr *laddr)
{
	static struct llc_addr null_addr;
	struct sock *rc = __llc_lookup_listener(sap, laddr);

	if (!rc)
		rc = __llc_lookup_listener(sap, &null_addr);

	return rc;
}
