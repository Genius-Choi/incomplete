matching_model_microcode(struct microcode_header_intel *mc_header,
			unsigned long sig)
{
	u8 x86, x86_model;
	u8 x86_ucode, x86_model_ucode;
	struct extended_sigtable *ext_header;
	unsigned long total_size = get_totalsize(mc_header);
	unsigned long data_size = get_datasize(mc_header);
	int ext_sigcount, i;
	struct extended_signature *ext_sig;

	x86 = get_x86_family(sig);
	x86_model = get_x86_model(sig);

	x86_ucode = get_x86_family(mc_header->sig);
	x86_model_ucode = get_x86_model(mc_header->sig);

	if (x86 == x86_ucode && x86_model == x86_model_ucode)
		return UCODE_OK;

	/* Look for ext. headers: */
	if (total_size <= data_size + MC_HEADER_SIZE)
		return UCODE_NFOUND;

	ext_header = (struct extended_sigtable *)
		     mc_header + data_size + MC_HEADER_SIZE;
	ext_sigcount = ext_header->count;
	ext_sig = (void *)ext_header + EXT_HEADER_SIZE;

	for (i = 0; i < ext_sigcount; i++) {
		x86_ucode = get_x86_family(ext_sig->sig);
		x86_model_ucode = get_x86_model(ext_sig->sig);

		if (x86 == x86_ucode && x86_model == x86_model_ucode)
			return UCODE_OK;

		ext_sig++;
	}

	return UCODE_NFOUND;
}
