static void setsymord(ELFOBJ* eobj, ut32 ord, RBinSymbol *ptr) {
	if (!eobj->symbols_by_ord || ord >= eobj->symbols_by_ord_size) {
		return;
	}
	free (eobj->symbols_by_ord[ord]);
	eobj->symbols_by_ord[ord] = r_mem_dup (ptr, sizeof (RBinSymbol));
}
