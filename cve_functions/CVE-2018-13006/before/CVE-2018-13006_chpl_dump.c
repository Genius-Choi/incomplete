GF_Err chpl_dump(GF_Box *a, FILE * trace)
{
	u32 i, count;
	char szDur[20];
	GF_ChapterListBox *p = (GF_ChapterListBox *)a;
	gf_isom_box_dump_start(a, "ChapterListBox", trace);
	fprintf(trace, ">\n");

	if (p->size) {
		count = gf_list_count(p->list);
		for (i=0; i<count; i++) {
			GF_ChapterEntry *ce = (GF_ChapterEntry *)gf_list_get(p->list, i);
			fprintf(trace, "<Chapter name=\"");
			dump_escape_string(trace, ce->name);
			fprintf(trace, "\" startTime=\"%s\" />\n", format_duration(ce->start_time, 1000*10000, szDur));
		}
	} else {
		fprintf(trace, "<Chapter name=\"\" startTime=\"\"/>\n");
	}

	gf_isom_box_dump_done("ChapterListBox", a, trace);
	return GF_OK;
}
