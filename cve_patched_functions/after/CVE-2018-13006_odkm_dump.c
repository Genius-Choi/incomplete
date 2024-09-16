GF_Err odkm_dump(GF_Box *a, FILE * trace)
{
	GF_OMADRMKMSBox *ptr = (GF_OMADRMKMSBox*)a;
	gf_isom_box_dump_start(a, "OMADRMKMSBox", trace);

	fprintf(trace, ">\n");
	if (ptr->hdr) gf_isom_box_dump((GF_Box *)ptr->hdr, trace);
	if (ptr->fmt) gf_isom_box_dump((GF_Box *)ptr->fmt, trace);
	gf_isom_box_dump_done("OMADRMKMSBox", a, trace);
	return GF_OK;
}
