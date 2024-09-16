static RBinAddr* binsym(RBinFile *bf, int sym) {
	struct Elf_(r_bin_elf_obj_t)* obj = bf->o->bin_obj;
	RBinAddr *ret = NULL;
	ut64 addr = 0LL;

	switch (sym) {
	case R_BIN_SYM_ENTRY:
		addr = Elf_(r_bin_elf_get_entry_offset) (bf->o->bin_obj);
		break;
	case R_BIN_SYM_MAIN:
		addr = Elf_(r_bin_elf_get_main_offset) (bf->o->bin_obj);
		break;
	case R_BIN_SYM_INIT:
		addr = Elf_(r_bin_elf_get_init_offset) (bf->o->bin_obj);
		break;
	case R_BIN_SYM_FINI:
		addr = Elf_(r_bin_elf_get_fini_offset) (bf->o->bin_obj);
		break;
	}
	if (addr && addr != UT64_MAX && (ret = R_NEW0 (RBinAddr))) {
		struct Elf_(r_bin_elf_obj_t) *bin = bf->o->bin_obj;
		bool is_arm = bin->ehdr.e_machine == EM_ARM;
		ret->paddr = addr;
		ret->vaddr = Elf_(r_bin_elf_p2v) (obj, addr);
		if (is_arm && addr & 1) {
			ret->bits = 16;
			ret->vaddr--; 
			ret->paddr--; 
		}
	}
	return ret;
}
