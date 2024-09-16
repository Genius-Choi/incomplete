jas_iccattrval_t *jas_iccprof_getattr(jas_iccprof_t *prof,
  jas_iccattrname_t name)
{
	int i;
	jas_iccattrval_t *attrval;
	if ((i = jas_iccattrtab_lookup(prof->attrtab, name)) < 0)
		goto error;
	if (!(attrval = jas_iccattrval_clone(prof->attrtab->attrs[i].val)))
		goto error;
	return attrval;
error:
	return 0;
}
