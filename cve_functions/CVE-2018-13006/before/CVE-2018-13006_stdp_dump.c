GF_Err stdp_dump(GF_Box *a, FILE * trace)
{
	GF_DegradationPriorityBox *p;
	u32 i;

	p = (GF_DegradationPriorityBox *)a;
	gf_isom_box_dump_start(a, "DegradationPriorityBox", trace);
	fprintf(trace, "EntryCount=\"%d\">\n", p->nb_entries);

	if (!p->priorities && p->size) {
		fprintf(trace, "<!--Warning: No Degradation Priority indications-->\n");
	} else {
		for (i=0; i<p->nb_entries; i++) {
			fprintf(trace, "<DegradationPriorityEntry DegradationPriority=\"%d\"/>\n", p->priorities[i]);
		}
	}
	if (!p->size) {
		fprintf(trace, "<DegradationPriorityEntry DegradationPriority=\"\"/>\n");
	}
	gf_isom_box_dump_done("DegradationPriorityBox", a, trace);
	return GF_OK;
}
