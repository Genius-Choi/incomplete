static int bin_exports(RCore *r, int mode, ut64 laddr, int va, ut64 at, const char *name, const char *args) {
	return bin_symbols_internal (r, mode, laddr, va, at, name, true, args);
}
