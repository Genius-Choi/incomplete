int main(int argc, char **argv)
{
    int n;                          /* general index */
    int noop;                       /* true to suppress option decoding */
    unsigned long done;             /* number of named files processed */
    char *opts, *p;                 /* environment default options, marker */

    /* initialize globals */
    g.outf = NULL;
    g.first = 1;
    g.hname = NULL;

    /* save pointer to program name for error messages */
    p = strrchr(argv[0], '/');
    p = p == NULL ? argv[0] : p + 1;
    g.prog = *p ? p : "pigz";

    /* prepare for interrupts and logging */
    signal(SIGINT, cut_short);
#ifndef NOTHREAD
    yarn_prefix = g.prog;           /* prefix for yarn error messages */
    yarn_abort = cut_short;         /* call on thread error */
#endif
#ifdef DEBUG
    gettimeofday(&start, NULL);     /* starting time for log entries */
    log_init();                     /* initialize logging */
#endif

    /* set all options to defaults */
    defaults();

    /* process user environment variable defaults in GZIP */
    opts = getenv("GZIP");
    if (opts != NULL) {
        while (*opts) {
            while (*opts == ' ' || *opts == '\t')
                opts++;
            p = opts;
            while (*p && *p != ' ' && *p != '\t')
                p++;
            n = *p;
            *p = 0;
            if (option(opts))
                bail("cannot provide files in GZIP environment variable", "");
            opts = p + (n ? 1 : 0);
        }
        option(NULL);
    }

    /* process user environment variable defaults in PIGZ as well */
    opts = getenv("PIGZ");
    if (opts != NULL) {
        while (*opts) {
            while (*opts == ' ' || *opts == '\t')
                opts++;
            p = opts;
            while (*p && *p != ' ' && *p != '\t')
                p++;
            n = *p;
            *p = 0;
            if (option(opts))
                bail("cannot provide files in PIGZ environment variable", "");
            opts = p + (n ? 1 : 0);
        }
        option(NULL);
    }

    /* decompress if named "unpigz" or "gunzip", to stdout if "*cat" */
    if (strcmp(g.prog, "unpigz") == 0 || strcmp(g.prog, "gunzip") == 0) {
        if (!g.decode)
            g.headis >>= 2;
        g.decode = 1;
    }
    if ((n = strlen(g.prog)) > 2 && strcmp(g.prog + n - 3, "cat") == 0) {
        if (!g.decode)
            g.headis >>= 2;
        g.decode = 1;
        g.pipeout = 1;
    }

    /* if no arguments and compressed data to or from a terminal, show help */
    if (argc < 2 && isatty(g.decode ? 0 : 1))
        help();

    /* process command-line arguments, no options after "--" */
    done = noop = 0;
    for (n = 1; n < argc; n++)
        if (noop == 0 && strcmp(argv[n], "--") == 0) {
            noop = 1;
            option(NULL);
        }
        else if (noop || option(argv[n])) { /* true if file name, process it */
            if (done == 1 && g.pipeout && !g.decode && !g.list && g.form > 1)
                complain("warning: output will be concatenated zip files -- "
                         "will not be able to extract");
            process(strcmp(argv[n], "-") ? argv[n] : NULL);
            done++;
        }
    option(NULL);

    /* list stdin or compress stdin to stdout if no file names provided */
    if (done == 0)
        process(NULL);

    /* done -- release resources, show log */
    new_opts();
    log_dump();
    return 0;
}
