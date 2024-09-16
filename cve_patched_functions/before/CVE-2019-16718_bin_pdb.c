static int bin_pdb(RCore *core, int mode) {
	ut64 baddr = r_bin_get_baddr (core->bin);
	return r_core_pdb_info (core, core->bin->file, baddr, mode);
}
