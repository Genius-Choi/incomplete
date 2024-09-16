static RList *maps(RBinFile *bf) {
	if (bf && bf->o) {
		return Elf_(r_bin_elf_get_maps)(bf->o->bin_obj);
	}
	return NULL;
}
