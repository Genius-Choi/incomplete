int jas_iccprof_setattr(jas_iccprof_t *prof, jas_iccattrname_t name,
  jas_iccattrval_t *val)
{
	int i;
	if ((i = jas_iccattrtab_lookup(prof->attrtab, name)) >= 0) {
		if (val) {
			if (jas_iccattrtab_replace(prof->attrtab, i, name, val))
				goto error;
		} else {
			jas_iccattrtab_delete(prof->attrtab, i);
		}
	} else {
		if (val) {
			if (jas_iccattrtab_add(prof->attrtab, -1, name, val))
				goto error;
		} else {
			/* NOP */
		}
	}
	return 0;
error:
	return -1;
}
