static jas_iccattrtab_t *jas_iccattrtab_copy(jas_iccattrtab_t *attrtab)
{
	jas_iccattrtab_t *newattrtab;
	int i;
	if (!(newattrtab = jas_iccattrtab_create()))
		goto error;
	for (i = 0; i < attrtab->numattrs; ++i) {
		if (jas_iccattrtab_add(newattrtab, i, attrtab->attrs[i].name,
		  attrtab->attrs[i].val))
			goto error;
	}
	return newattrtab;
error:
	return 0;
}
