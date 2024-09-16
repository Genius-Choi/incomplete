compare_blob(const struct xdr_netobj *o1, const struct xdr_netobj *o2)
{
	if (o1->len < o2->len)
		return -1;
	if (o1->len > o2->len)
		return 1;
	return memcmp(o1->data, o2->data, o1->len);
}
