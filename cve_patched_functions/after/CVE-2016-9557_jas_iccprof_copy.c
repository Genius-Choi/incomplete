jas_iccprof_t *jas_iccprof_copy(jas_iccprof_t *prof)
{
	jas_iccprof_t *newprof;
	newprof = 0;
	if (!(newprof = jas_iccprof_create()))
		goto error;
	newprof->hdr = prof->hdr;
	newprof->tagtab.numents = 0;
	newprof->tagtab.ents = 0;
	assert(newprof->attrtab);
	jas_iccattrtab_destroy(newprof->attrtab);
	if (!(newprof->attrtab = jas_iccattrtab_copy(prof->attrtab)))
		goto error;
	return newprof;
error:
	if (newprof)
		jas_iccprof_destroy(newprof);
	return 0;
}
