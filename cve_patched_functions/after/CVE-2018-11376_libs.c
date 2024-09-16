static RList* libs(RBinFile *bf) {
	struct r_bin_elf_lib_t *libs = NULL;
	RList *ret = NULL;
	char *ptr = NULL;
	int i;

	if (!bf || !bf->o || !bf->o->bin_obj) {
		return NULL;
	}
	if (!(ret = r_list_newf (free))) {
		return NULL;
	}
	if (!(libs = Elf_(r_bin_elf_get_libs) (bf->o->bin_obj))) {
		return ret;
	}
	for (i = 0; !libs[i].last; i++) {
		ptr = strdup (libs[i].name);
		r_list_append (ret, ptr);
	}
	free (libs);
	return ret;
}
