static Sdb* get_sdb(RBinFile *bf) {
	RBinObject *o = bf->o;
	if (o && o->bin_obj) {
		struct Elf_(r_bin_elf_obj_t) *bin = (struct Elf_(r_bin_elf_obj_t) *) o->bin_obj;
		return bin->kv;
	}
	return NULL;
}
