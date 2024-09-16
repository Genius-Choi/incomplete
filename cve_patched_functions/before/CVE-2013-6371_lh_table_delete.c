int lh_table_delete(struct lh_table *t, const void *k)
{
	struct lh_entry *e = lh_table_lookup_entry(t, k);
	if(!e) return -1;
	return lh_table_delete_entry(t, e);
}
