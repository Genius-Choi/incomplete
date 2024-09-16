void lh_table_free(struct lh_table *t)
{
	struct lh_entry *c;
	for(c = t->head; c != NULL; c = c->next) {
		if(t->free_fn) {
			t->free_fn(c);
		}
	}
	free(t->table);
	free(t);
}
