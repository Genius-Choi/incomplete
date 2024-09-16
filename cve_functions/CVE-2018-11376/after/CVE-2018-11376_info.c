static RBinInfo* info(RBinFile *bf) {
	RBinInfo *ret = NULL;
	char *str;

	if (!(ret = R_NEW0 (RBinInfo))) {
		return NULL;
	}
	ret->lang = "c";
	ret->file = bf->file
		? strdup (bf->file)
		: NULL;
	void *obj = bf->o->bin_obj;
	if ((str = Elf_(r_bin_elf_get_rpath)(obj))) {
		ret->rpath = strdup (str);
		free (str);
	} else {
		ret->rpath = strdup ("NONE");
	}
	if (!(str = Elf_(r_bin_elf_get_file_type) (obj))) {
		free (ret);
		return NULL;
	}
	ret->type = str;
	ret->has_pi = (strstr (str, "DYN"))? 1: 0;
	ret->has_lit = true;
	ret->has_canary = has_canary (bf);
	if (!(str = Elf_(r_bin_elf_get_elf_class) (obj))) {
		free (ret);
		return NULL;
	}
	ret->bclass = str;
	if (!(str = Elf_(r_bin_elf_get_osabi_name) (obj))) {
		free (ret);
		return NULL;
	}
	ret->os = str;
	if (!(str = Elf_(r_bin_elf_get_osabi_name) (obj))) {
		free (ret);
		return NULL;
	}
	ret->subsystem = str;
	if (!(str = Elf_(r_bin_elf_get_machine_name) (obj))) {
		free (ret);
		return NULL;
	}
	ret->machine = str;
	if (!(str = Elf_(r_bin_elf_get_arch) (obj))) {
		free (ret);
		return NULL;
	}
	ret->arch = str;
	ret->rclass = strdup ("elf");
	ret->bits = Elf_(r_bin_elf_get_bits) (obj);
	if (!strcmp (ret->arch, "avr")) {
		ret->bits = 16;
	}
	ret->big_endian = Elf_(r_bin_elf_is_big_endian) (obj);
	ret->has_va = Elf_(r_bin_elf_has_va) (obj);
	ret->has_nx = Elf_(r_bin_elf_has_nx) (obj);
	ret->intrp = Elf_(r_bin_elf_intrp) (obj);
	ret->dbg_info = 0;
	if (!Elf_(r_bin_elf_get_stripped) (obj)) {
		ret->dbg_info |= R_BIN_DBG_LINENUMS | R_BIN_DBG_SYMS | R_BIN_DBG_RELOCS;
	} else {
		ret->dbg_info |= R_BIN_DBG_STRIPPED;
	}
	if (Elf_(r_bin_elf_get_static) (obj)) {
		ret->dbg_info |= R_BIN_DBG_STATIC;
	}
	RBinElfSymbol *symbol;
	if (!(symbol = Elf_(r_bin_elf_get_symbols) (obj))) {
		return ret;
	}
	int i;
	for (i = 0; !symbol[i].last; i++) {
		if (!strncmp (symbol[i].name, "type.", 5)) {
			ret->lang = "go";
			break;
		}
	}
	return ret;
}
