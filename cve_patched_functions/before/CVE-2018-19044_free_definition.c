free_definition(void *d)
{
	def_t *def = d;

	FREE(def->name);
	FREE_PTR(def->value);
	FREE(def);
}
