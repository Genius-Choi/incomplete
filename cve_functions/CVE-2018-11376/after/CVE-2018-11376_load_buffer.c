static void * load_buffer(RBinFile *bf, RBuffer *buf, ut64 loadaddr, Sdb *sdb) {
	struct Elf_(r_bin_elf_obj_t) *res;
	if (!buf) {
		return NULL;
	}
	res = Elf_(r_bin_elf_new_buf) (buf, bf->rbin->verbose);
	if (res) {
		sdb_ns_set (sdb, "info", res->kv);
	}
	return res;
}
