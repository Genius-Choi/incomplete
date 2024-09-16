static void usage(int error)
{
	FILE *out = error ? stderr : stdout;

	print_version(out);
	fprintf(out,
		"Usage:\n"
		" %1$s -L <label> | -U <uuid>\n\n"
		" %1$s [-c <file>] [-ghlLv] [-o <format>] [-s <tag>] \n"
		"       [-t <token>] [<dev> ...]\n\n"
		" %1$s -p [-s <tag>] [-O <offset>] [-S <size>] \n"
		"       [-o <format>] <dev> ...\n\n"
		" %1$s -i [-s <tag>] [-o <format>] <dev> ...\n\n"
		"Options:\n"
		" -c <file>   read from <file> instead of reading from the default\n"
		"               cache file (-c /dev/null means no cache)\n"
		" -d          don't encode non-printing characters\n"
		" -h          print this usage message and exit\n"
		" -g          garbage collect the blkid cache\n"
		" -o <format> output format; can be one of:\n"
		"               value, device, export or full; (default: full)\n"
		" -k          list all known filesystems/RAIDs and exit\n"
		" -s <tag>    show specified tag(s) (default show all tags)\n"
		" -t <token>  find device with a specific token (NAME=value pair)\n"
		" -l          look up only first device with token specified by -t\n"
		" -L <label>  convert LABEL to device name\n"
		" -U <uuid>   convert UUID to device name\n"
		" -V          print version and exit\n"
		" <dev>       specify device(s) to probe (default: all devices)\n\n"
		"Low-level probing options:\n"
		" -p          low-level superblocks probing (bypass cache)\n"
		" -i          gather information about I/O limits\n"
		" -S <size>   overwrite device size\n"
		" -O <offset> probe at the given offset\n"
		" -u <list>   filter by \"usage\" (e.g. -u filesystem,raid)\n"
		" -n <list>   filter by filesystem type (e.g. -n vfat,ext3)\n"
		"\n", program_invocation_short_name);

	exit(error);
}
