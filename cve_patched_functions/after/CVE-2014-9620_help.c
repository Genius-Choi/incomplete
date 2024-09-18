help(void)
{
	(void)fputs(
"Usage: file [OPTION...] [FILE...]\n"
"Determine type of FILEs.\n"
"\n", stdout);
#define OPT(shortname, longname, opt, doc)      \
	fprintf(stdout, "  -%c, --" longname, shortname), \
	docprint(doc);
#define OPT_LONGONLY(longname, opt, doc)        \
	fprintf(stdout, "      --" longname),	\
	docprint(doc);
#include "file_opts.h"
#undef OPT
#undef OPT_LONGONLY
	fprintf(stdout, "\nReport bugs to http://bugs.gw.com/\n");
	exit(0);
}
