static input_translation_t *GetTranslationTable(exporter_ipfix_domain_t *exporter, uint16_t id) {
input_translation_t *table;

	if ( exporter->current_table && ( exporter->current_table->id == id ) )
		return exporter->current_table;

	table = exporter->input_translation_table;
	while ( table ) {
		if ( table->id == id ) {
			exporter->current_table = table;
			return table;
		}

		table = table->next;
	}

	dbg_printf("[%u] Get translation table %u: %s\n", exporter->info.id, id, table == NULL ? "not found" : "found");

	exporter->current_table = table;
	return table;

} // End of GetTranslationTable
