static int parse_dylib(struct MACH0_(obj_t)* bin, ut64 off) {
	struct dylib_command dl;
	int lib, len;
	ut8 sdl[sizeof (struct dylib_command)] = {0};

	if (off > bin->size || off + sizeof (struct dylib_command) > bin->size)
		return false;
	lib = bin->nlibs - 1;

	if (!(bin->libs = realloc (bin->libs, bin->nlibs * R_BIN_MACH0_STRING_LENGTH))) {
		perror ("realloc (libs)");
		return false;
	}
	len = r_buf_read_at (bin->b, off, sdl, sizeof (struct dylib_command));
	if (len < 1) {
		bprintf ("Error: read (dylib)\n");
		return false;
	}
	dl.cmd = r_read_ble32 (&sdl[0], bin->big_endian);
	dl.cmdsize = r_read_ble32 (&sdl[4], bin->big_endian);
	dl.dylib.name = r_read_ble32 (&sdl[8], bin->big_endian);
	dl.dylib.timestamp = r_read_ble32 (&sdl[12], bin->big_endian);
	dl.dylib.current_version = r_read_ble32 (&sdl[16], bin->big_endian);
	dl.dylib.compatibility_version = r_read_ble32 (&sdl[20], bin->big_endian);

	if (off + dl.dylib.name > bin->size ||\
	  off + dl.dylib.name + R_BIN_MACH0_STRING_LENGTH > bin->size)
		return false;

	len = r_buf_read_at (bin->b, off+dl.dylib.name, (ut8*)bin->libs[lib], R_BIN_MACH0_STRING_LENGTH);
	if (len < 1) {
		bprintf ("Error: read (dylib str)");
		return false;
	}
	return true;
}
