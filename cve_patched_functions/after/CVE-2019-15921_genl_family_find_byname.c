static const struct genl_family *genl_family_find_byname(char *name)
{
	const struct genl_family *family;
	unsigned int id;

	idr_for_each_entry(&genl_fam_idr, family, id)
		if (strcmp(family->name, name) == 0)
			return family;

	return NULL;
}
