static void print_version(FILE *out)
{
	fprintf(out, "%s from %s  (libblkid %s, %s)\n",
		program_invocation_short_name, PACKAGE_STRING,
		LIBBLKID_VERSION, LIBBLKID_DATE);
}
