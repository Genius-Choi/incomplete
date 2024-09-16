GF_Err rely_dump(GF_Box *a, FILE * trace)
{
	GF_RelyHintBox *p;
	p = (GF_RelyHintBox *)a;
	gf_isom_box_dump_start(a, "RelyTransmissionBox", trace);
	fprintf(trace, "Prefered=\"%d\" required=\"%d\">\n", p->prefered, p->required);
	gf_isom_box_dump_done("RelyTransmissionBox", a, trace);
	return GF_OK;
}
