static char* regstate(RBinFile *bf) {
	struct Elf_(r_bin_elf_obj_t) *obj = bf->o->bin_obj;
	if (obj->ehdr.e_machine != EM_AARCH64 &&
		obj->ehdr.e_machine != EM_ARM &&
		obj->ehdr.e_machine != EM_386 &&
		obj->ehdr.e_machine != EM_X86_64) {
		eprintf ("Cannot retrieve regstate on: %s (not yet supported)\n",
					Elf_(r_bin_elf_get_machine_name)(obj));
		return NULL;
	}

	int len = 0;
	ut8 *regs = Elf_(r_bin_elf_grab_regstate) (obj, &len);
	char *hexregs = (regs && len > 0) ? r_hex_bin2strdup (regs, len) : NULL;

	free (regs);
	return hexregs;
}
