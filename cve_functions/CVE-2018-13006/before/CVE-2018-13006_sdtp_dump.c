GF_Err sdtp_dump(GF_Box *a, FILE * trace)
{
	GF_SampleDependencyTypeBox *p;
	u32 i;

	p = (GF_SampleDependencyTypeBox*)a;
	gf_isom_box_dump_start(a, "SampleDependencyTypeBox", trace);
	fprintf(trace, "SampleCount=\"%d\">\n", p->sampleCount);

	if (!p->sample_info && p->size) {
		fprintf(trace, "<!--Warning: No sample dependencies indications-->\n");
	} else {
		for (i=0; i<p->sampleCount; i++) {
			u8 flag = p->sample_info[i];
			fprintf(trace, "<SampleDependencyEntry ");
			switch ( (flag >> 4) & 3) {
			case 0:
				fprintf(trace, "dependsOnOther=\"unknown\" ");
				break;
			case 1:
				fprintf(trace, "dependsOnOther=\"yes\" ");
				break;
			case 2:
				fprintf(trace, "dependsOnOther=\"no\" ");
				break;
			case 3:
				fprintf(trace, "dependsOnOther=\"RESERVED\" ");
				break;
			}
			switch ( (flag >> 2) & 3) {
			case 0:
				fprintf(trace, "dependedOn=\"unknown\" ");
				break;
			case 1:
				fprintf(trace, "dependedOn=\"yes\" ");
				break;
			case 2:
				fprintf(trace, "dependedOn=\"no\" ");
				break;
			case 3:
				fprintf(trace, "dependedOn=\"RESERVED\" ");
				break;
			}
			switch ( flag & 3) {
			case 0:
				fprintf(trace, "hasRedundancy=\"unknown\" ");
				break;
			case 1:
				fprintf(trace, "hasRedundancy=\"yes\" ");
				break;
			case 2:
				fprintf(trace, "hasRedundancy=\"no\" ");
				break;
			case 3:
				fprintf(trace, "hasRedundancy=\"RESERVED\" ");
				break;
			}
			fprintf(trace, " />\n");
		}
	}
	if (!p->size) {
		fprintf(trace, "<SampleDependencyEntry dependsOnOther=\"unknown|yes|no|RESERVED\" dependedOn=\"unknown|yes|no|RESERVED\" hasRedundancy=\"unknown|yes|no|RESERVED\"/>\n");
	}
	gf_isom_box_dump_done("SampleDependencyTypeBox", a, trace);
	return GF_OK;
}
