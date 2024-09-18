static jas_iccprof_t *jas_iccprof_create()
{
	jas_iccprof_t *prof;
	prof = 0;
	if (!(prof = jas_malloc(sizeof(jas_iccprof_t)))) {
		goto error;
	}
	if (!(prof->attrtab = jas_iccattrtab_create()))
		goto error;
	memset(&prof->hdr, 0, sizeof(jas_icchdr_t));
	prof->tagtab.numents = 0;
	prof->tagtab.ents = 0;
	return prof;
error:
	if (prof)
		jas_iccprof_destroy(prof);
	return 0;
}
