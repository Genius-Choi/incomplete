kex_assemble_names(const char *def, char **list)
{
	char *ret;

	if (list == NULL || *list == NULL || **list == '\0') {
		*list = strdup(def);
		return 0;
	}
	if (**list != '+') {
		return 0;
	}

	if ((ret = kex_names_cat(def, *list + 1)) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	free(*list);
	*list = ret;
	return 0;
}
