static RList* imports(RBinFile *bf) {
	struct Elf_(r_bin_elf_obj_t) *bin = NULL;
	RBinElfSymbol *import = NULL;
	RBinImport *ptr = NULL;
	RList *ret = NULL;
	int i;

	if (!bf || !bf->o || !bf->o->bin_obj) {
		return NULL;
	}
	bin = bf->o->bin_obj;
	if (!(ret = r_list_newf (r_bin_import_free))) {
		return NULL;
	}
	if (!(import = Elf_(r_bin_elf_get_imports) (bin))) {
		r_list_free (ret);
		return NULL;
	}
	for (i = 0; !import[i].last; i++) {
		if (!(ptr = R_NEW0 (RBinImport))) {
			break;
		}
		ptr->name = strdup (import[i].name);
		ptr->bind = r_str_const (import[i].bind);
		ptr->type = r_str_const (import[i].type);
		ptr->ordinal = import[i].ordinal;
		(void)setimpord (bin, ptr->ordinal, ptr);
		r_list_append (ret, ptr);
	}
	return ret;
}
