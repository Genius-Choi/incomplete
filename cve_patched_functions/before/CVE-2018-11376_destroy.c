static int destroy(RBinFile *bf) {
	int i;
	ELFOBJ* eobj = bf->o->bin_obj;
	if (eobj && eobj->imports_by_ord) {
		for (i = 0; i < eobj->imports_by_ord_size; i++) {
			RBinImport *imp = eobj->imports_by_ord[i];
			if (imp) {
				free (imp->name);
				free (imp);
				eobj->imports_by_ord[i] = NULL;
			}
		}
		R_FREE (eobj->imports_by_ord);
	}
	Elf_(r_bin_elf_free) ((struct Elf_(r_bin_elf_obj_t)*)bf->o->bin_obj);
	return true;
}
