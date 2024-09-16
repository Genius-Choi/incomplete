struct lh_table* lh_table_new(int size, const char *name,
			      lh_entry_free_fn *free_fn,
			      lh_hash_fn *hash_fn,
			      lh_equal_fn *equal_fn)
{
	int i;
	struct lh_table *t;

	t = (struct lh_table*)calloc(1, sizeof(struct lh_table));
	if(!t) lh_abort("lh_table_new: calloc failed\n");
	t->count = 0;
	t->size = size;
	t->name = name;
	t->table = (struct lh_entry*)calloc(size, sizeof(struct lh_entry));
	if(!t->table) lh_abort("lh_table_new: calloc failed\n");
	t->free_fn = free_fn;
	t->hash_fn = hash_fn;
	t->equal_fn = equal_fn;
	for(i = 0; i < size; i++) t->table[i].k = LH_EMPTY;
	return t;
}
