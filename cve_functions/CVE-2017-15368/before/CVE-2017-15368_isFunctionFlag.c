static bool isFunctionFlag(const char *n) {
	return (!strncmp (n, "sym.func.", 9)
	|| !strncmp (n, "method.", 7)
	|| !strncmp (n, "sym.", 7)
	|| !strncmp (n, "func.", 5)
	|| !strncmp (n, "fcn.0", 5));
}
