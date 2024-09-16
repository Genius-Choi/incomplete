struct lh_table* lh_kchar_table_new(int size, const char *name,
				    lh_entry_free_fn *free_fn)
{
	return lh_table_new(size, name, free_fn, lh_char_hash, lh_char_equal);
}
