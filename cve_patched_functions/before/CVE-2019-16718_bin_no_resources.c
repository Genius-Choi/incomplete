static void bin_no_resources(RCore *r, int mode) {
	if (IS_MODE_JSON (mode)) {
		r_cons_printf ("[]");
	}
}
