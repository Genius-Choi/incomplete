const void* lh_table_lookup(struct lh_table *t, const void *k)
{
	void *result;
	lh_table_lookup_ex(t, k, &result);
	return result;
}
