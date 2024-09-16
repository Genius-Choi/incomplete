void lh_table_resize(struct lh_table *t, int new_size)
{
	struct lh_table *new_t;
	struct lh_entry *ent;

	new_t = lh_table_new(new_size, t->name, NULL, t->hash_fn, t->equal_fn);
	ent = t->head;
	while(ent) {
		lh_table_insert(new_t, ent->k, ent->v);
		ent = ent->next;
	}
	free(t->table);
	t->table = new_t->table;
	t->size = new_size;
	t->head = new_t->head;
	t->tail = new_t->tail;
	t->resizes++;
	free(new_t);
}
