static int entersafe_create_file(sc_card_t *card, sc_file_t *file)
{	
	 SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);
	 
	 if (file->type == SC_FILE_TYPE_WORKING_EF) {
		  sc_entersafe_create_data data;
		  memset(&data,0,sizeof(data));

		  data.data.ef.file_id[0] = (file->id>>8)&0xFF;	
		  data.data.ef.file_id[1] = file->id&0xFF;	
		  data.data.ef.size[0] = (file->size>>8)&0xFF;
		  data.data.ef.size[1] = file->size&0xFF;
		  memset(data.data.ef.ac,ENTERSAFE_AC_ALWAYS,sizeof(data.data.ef.ac));
		  data.data.ef.ac[0] = process_acl_entry(file,SC_AC_OP_READ,ENTERSAFE_AC_ALWAYS);
		  data.data.ef.ac[1] = process_acl_entry(file,SC_AC_OP_UPDATE,ENTERSAFE_AC_ALWAYS);

		  return entersafe_create_ef(card, &data);
	 } else
		  return SC_ERROR_INVALID_ARGUMENTS;
}
