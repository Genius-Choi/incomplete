GF_Err schm_dump(GF_Box *a, FILE * trace)
{
	GF_SchemeTypeBox *p;
	p = (GF_SchemeTypeBox *)a;
	gf_isom_box_dump_start(a, "SchemeTypeBox", trace);
	fprintf(trace, "scheme_type=\"%s\" scheme_version=\"%d\" ", gf_4cc_to_str(p->scheme_type), p->scheme_version);
	if (p->URI) fprintf(trace, "scheme_uri=\"%s\"", p->URI);
	fprintf(trace, ">\n");

	gf_isom_box_dump_done("SchemeTypeBox", a, trace);
	return GF_OK;
}
