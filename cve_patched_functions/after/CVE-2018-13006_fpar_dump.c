GF_Err fpar_dump(GF_Box *a, FILE * trace)
{
	u32 i;
	FilePartitionBox *ptr = (FilePartitionBox *) a;
	gf_isom_box_dump_start(a, "FilePartitionBox", trace);

	fprintf(trace, "itemID=\"%d\" FEC_encoding_ID=\"%d\" FEC_instance_ID=\"%d\" max_source_block_length=\"%d\" encoding_symbol_length=\"%d\" max_number_of_encoding_symbols=\"%d\" ", ptr->itemID, ptr->FEC_encoding_ID, ptr->FEC_instance_ID, ptr->max_source_block_length, ptr->encoding_symbol_length, ptr->max_number_of_encoding_symbols);

	if (ptr->scheme_specific_info)
		dump_data_attribute(trace, "scheme_specific_info", (char*)ptr->scheme_specific_info, (u32)strlen(ptr->scheme_specific_info) );

	fprintf(trace, ">\n");

	for (i=0; i<ptr->nb_entries; i++) {
		fprintf(trace, "<FilePartitionBoxEntry block_count=\"%d\" block_size=\"%d\"/>\n", ptr->entries[i].block_count, ptr->entries[i].block_size);
	}
	if (!ptr->size) {
		fprintf(trace, "<FilePartitionBoxEntry block_count=\"\" block_size=\"\"/>\n");
	}

	gf_isom_box_dump_done("FilePartitionBox", a, trace);
	return GF_OK;
}
