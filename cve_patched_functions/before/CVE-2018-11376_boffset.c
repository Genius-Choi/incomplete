static ut64 boffset(RBinFile *bf) {
	return Elf_(r_bin_elf_get_boffset) (bf->o->bin_obj);
}
