static bool load(RBinFile *bf) {
	const ut8 *bytes = bf ? r_buf_buffer (bf->buf) : NULL;
	ut64 sz = bf ? r_buf_size (bf->buf): 0;
	if (!bf || !bf->o) {
		return false;
	}
	bf->o->bin_obj = load_bytes (bf, bytes, sz, bf->o->loadaddr, bf->sdb);
	return bf->o->bin_obj != NULL;
}
