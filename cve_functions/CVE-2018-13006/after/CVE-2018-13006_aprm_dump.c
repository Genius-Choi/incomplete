GF_Err aprm_dump(GF_Box *a, FILE * trace)
{
	GF_AdobeStdEncryptionParamsBox *ptr = (GF_AdobeStdEncryptionParamsBox *)a;
	if (!a) return GF_BAD_PARAM;
	gf_isom_box_dump_start(a, "AdobeStdEncryptionParamsBox", trace);
	fprintf(trace, ">\n");
	if (ptr->enc_info) gf_isom_box_dump((GF_Box *)ptr->enc_info, trace);
	if (ptr->key_info) gf_isom_box_dump((GF_Box *)ptr->key_info, trace);
	gf_isom_box_dump_done("AdobeStdEncryptionParamsBox", a, trace);
	return GF_OK;
}
