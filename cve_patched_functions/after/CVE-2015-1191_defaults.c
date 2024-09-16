local void defaults(void)
{
    g.level = Z_DEFAULT_COMPRESSION;
    /* default zopfli options as set by ZopfliInitOptions():
        verbose = 0
        numiterations = 15
        blocksplitting = 1
        blocksplittinglast = 0
        blocksplittingmax = 15
     */
    ZopfliInitOptions(&g.zopts);
#ifdef NOTHREAD
    g.procs = 1;
#else
    g.procs = nprocs(8);
#endif
    g.block = 131072UL;             /* 128K */
    g.rsync = 0;                    /* don't do rsync blocking */
    g.setdict = 1;                  /* initialize dictionary each thread */
    g.verbosity = 1;                /* normal message level */
    g.headis = 3;                   /* store/restore name and timestamp */
    g.pipeout = 0;                  /* don't force output to stdout */
    g.sufx = ".gz";                 /* compressed file suffix */
    g.decode = 0;                   /* compress */
    g.list = 0;                     /* compress */
    g.keep = 0;                     /* delete input file once compressed */
    g.force = 0;                    /* don't overwrite, don't compress links */
    g.recurse = 0;                  /* don't go into directories */
    g.form = 0;                     /* use gzip format */
}
