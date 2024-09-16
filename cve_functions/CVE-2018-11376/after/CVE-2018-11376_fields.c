static RList* fields(RBinFile *bf) {
	RList *ret = NULL;
	RBinField *ptr = NULL;
	struct r_bin_elf_field_t *field = NULL;
	int i;

	if (!(ret = r_list_new ())) {
		return NULL;
	}
	ret->free = free;
	if (!(field = Elf_(r_bin_elf_get_fields) (bf->o->bin_obj))) {
		return ret;
	}
	for (i = 0; !field[i].last; i++) {
		if (!(ptr = R_NEW0 (RBinField))) {
			break;
		}
		ptr->name = strdup (field[i].name);
		ptr->comment = NULL;
		ptr->vaddr = field[i].offset;
		ptr->paddr = field[i].offset;
		r_list_append (ret, ptr);
	}
	free (field);
	return ret;
}
