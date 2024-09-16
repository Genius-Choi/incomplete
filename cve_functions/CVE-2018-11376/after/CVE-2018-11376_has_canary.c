static bool has_canary(RBinFile *bf) {
	bool ret = false;
	RList* imports_list = imports (bf);
	RListIter *iter;
	RBinImport *import;
	if (imports_list) {
		r_list_foreach (imports_list, iter, import) {
			if (!strcmp (import->name, "__stack_chk_fail") || !strcmp (import->name, "__stack_smash_handler")) {
				ret = true;
				break;
			}
		}
		imports_list->free = r_bin_import_free;
		r_list_free (imports_list);
	}
	return ret;
}
