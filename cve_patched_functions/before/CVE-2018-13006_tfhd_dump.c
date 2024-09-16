GF_Err tfhd_dump(GF_Box *a, FILE * trace)
{
	GF_TrackFragmentHeaderBox *p;
	p = (GF_TrackFragmentHeaderBox *)a;
	gf_isom_box_dump_start(a, "TrackFragmentHeaderBox", trace);
	fprintf(trace, "TrackID=\"%u\"", p->trackID);

	if (p->flags & GF_ISOM_TRAF_BASE_OFFSET) {
		fprintf(trace, " BaseDataOffset=\""LLU"\"", p->base_data_offset);
	} else {
		fprintf(trace, " BaseDataOffset=\"%s\"", (p->flags & GF_ISOM_MOOF_BASE_OFFSET) ? "moof" : "moof-or-previous-traf");
	}

	if (p->flags & GF_ISOM_TRAF_SAMPLE_DESC)
		fprintf(trace, " SampleDescriptionIndex=\"%u\"", p->sample_desc_index);
	if (p->flags & GF_ISOM_TRAF_SAMPLE_DUR)
		fprintf(trace, " SampleDuration=\"%u\"", p->def_sample_duration);
	if (p->flags & GF_ISOM_TRAF_SAMPLE_SIZE)
		fprintf(trace, " SampleSize=\"%u\"", p->def_sample_size);

	if (p->flags & GF_ISOM_TRAF_SAMPLE_FLAGS) {
		frag_dump_sample_flags(trace, p->def_sample_flags);
	}

	fprintf(trace, ">\n");

	gf_isom_box_dump_done("TrackFragmentHeaderBox", a, trace);
	return GF_OK;
}
