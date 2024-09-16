static int load(RBinFile *arch) {
	const ut8 *bytes = r_buf_buffer (arch->buf);
	ut64 sz = r_buf_size (arch->buf);
	arch->o->bin_obj = load_bytes (arch, bytes, sz, arch->o->loadaddr, arch->sdb);
	return arch->o->bin_obj ? true : false;
}
