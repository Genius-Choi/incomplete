dump_definitions(void)
{
	def_t *def;
	element e;

	LIST_FOREACH(defs, def, e)
		log_message(LOG_INFO, "Defn %s = '%s'", def->name, def->value);
	log_message(LOG_INFO, "%s", "");
}
