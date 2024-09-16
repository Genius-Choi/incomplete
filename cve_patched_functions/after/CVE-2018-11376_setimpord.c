static inline bool setimpord(ELFOBJ* eobj, ut32 ord, RBinImport *ptr) {
	if (!eobj->imports_by_ord || ord >= eobj->imports_by_ord_size) {
		return false;
	}
	if (eobj->imports_by_ord[ord]) {
		free (eobj->imports_by_ord[ord]->name);
		free (eobj->imports_by_ord[ord]);
	}
	eobj->imports_by_ord[ord] = r_mem_dup (ptr, sizeof (RBinImport));
	eobj->imports_by_ord[ord]->name = strdup (ptr->name);
	return true;
}
