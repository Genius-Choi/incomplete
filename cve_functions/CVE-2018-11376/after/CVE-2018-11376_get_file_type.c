static int get_file_type(RBinFile *bf) {
	struct Elf_(r_bin_elf_obj_t) *obj = bf->o->bin_obj;
	char *type = Elf_(r_bin_elf_get_file_type (obj));
	return type? ((!strncmp (type, "CORE", 4)) ? R_BIN_TYPE_CORE : R_BIN_TYPE_DEFAULT) : -1;
}
