GF_Err diST_dump(GF_Box *a, FILE * trace)
{
	GF_DIMSScriptTypesBox *p = (GF_DIMSScriptTypesBox*)a;
	gf_isom_box_dump_start(a, "DIMSScriptTypesBox", trace);
	fprintf(trace, "types=\"%s\">\n", p->content_script_types);
	gf_isom_box_dump_done("DIMSScriptTypesBox", a, trace);
	return GF_OK;
}
