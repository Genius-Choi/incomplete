add_std_definition(const char *name, const char *value, char *(*fn)(void))
{
	def_t* def;

	def = MALLOC(sizeof(*def));
	def->name_len = strlen(name);
	def->name = MALLOC(def->name_len + 1);
	strcpy(def->name, name);
	if (value) {
		def->value_len = strlen(value);
		def->value = MALLOC(def->value_len + 1);
		strcpy(def->value, value);
	}
	def->fn = fn;

	if (!LIST_EXISTS(defs))
		defs = alloc_list(free_definition, NULL);
	list_add(defs, def);
}
