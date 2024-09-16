GF_Err stco_dump(GF_Box *a, FILE * trace)
{
	GF_ChunkOffsetBox *p;
	u32 i;

	p = (GF_ChunkOffsetBox *)a;
	gf_isom_box_dump_start(a, "ChunkOffsetBox", trace);
	fprintf(trace, "EntryCount=\"%d\">\n", p->nb_entries);

	if (!p->offsets && p->size) {
		fprintf(trace, "<!--Warning: No Chunk Offsets indications-->\n");
	} else {
		for (i=0; i<p->nb_entries; i++) {
			fprintf(trace, "<ChunkEntry offset=\"%u\"/>\n", p->offsets[i]);
		}
	}
	if (!p->size) {
		fprintf(trace, "<ChunkEntry offset=\"\"/>\n");
	}
	gf_isom_box_dump_done("ChunkOffsetBox", a, trace);
	return GF_OK;
}
