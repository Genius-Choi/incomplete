static ut64 baddr(RBinFile *bf) {
	return Elf_(r_bin_elf_get_baddr) (bf->o->bin_obj);
}
