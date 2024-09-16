GF_Err ipco_dump(GF_Box *a, FILE * trace)
{
	gf_isom_box_dump_start(a, "ItemPropertyContainerBox", trace);
	fprintf(trace, ">\n");
	gf_isom_box_dump_done("ItemPropertyContainerBox", a, trace);
	return GF_OK;
}
