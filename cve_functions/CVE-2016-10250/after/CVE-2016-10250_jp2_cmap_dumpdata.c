static void jp2_cmap_dumpdata(jp2_box_t *box, FILE *out)
{
	jp2_cmap_t *cmap = &box->data.cmap;
	unsigned int i;
	jp2_cmapent_t *ent;
	fprintf(out, "numchans = %d\n", (int) cmap->numchans);
	for (i = 0; i < cmap->numchans; ++i) {
		ent = &cmap->ents[i];
		fprintf(out, "cmptno=%d; map=%d; pcol=%d\n",
		  (int) ent->cmptno, (int) ent->map, (int) ent->pcol);
	}
}
