static void relocs_by_sym_free(HtKv *kv) {
	free (kv->key);
	free (kv->value);
}
