GF_Err m4ds_dump(GF_Box *a, FILE * trace)
{
	u32 i;
	GF_Descriptor *desc;
	GF_MPEG4ExtensionDescriptorsBox *p = (GF_MPEG4ExtensionDescriptorsBox *) a;
	gf_isom_box_dump_start(a, "MPEG4ExtensionDescriptorsBox", trace);
	fprintf(trace, ">\n");

	i=0;
	while ((desc = (GF_Descriptor *)gf_list_enum(p->descriptors, &i))) {
#ifndef GPAC_DISABLE_OD_DUMP
		gf_odf_dump_desc(desc, trace, 1, GF_TRUE);
#else
		fprintf(trace, "<!-- Object Descriptor Dumping disabled in this build of GPAC -->\n");
#endif
	}
	gf_isom_box_dump_done("MPEG4ExtensionDescriptorsBox", a, trace);
	return GF_OK;
}
