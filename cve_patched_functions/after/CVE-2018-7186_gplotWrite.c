gplotWrite(const char  *filename,
           GPLOT       *gplot)
{
FILE  *fp;

    PROCNAME("gplotWrite");

    if (!filename)
        return ERROR_INT("filename not defined", procName, 1);
    if (!gplot)
        return ERROR_INT("gplot not defined", procName, 1);

    if ((fp = fopenWriteStream(filename, "wb")) == NULL)
        return ERROR_INT("stream not opened", procName, 1);

    fprintf(fp, "Gplot Version %d\n", GPLOT_VERSION_NUMBER);
    fprintf(fp, "Rootname: %s\n", gplot->rootname);
    fprintf(fp, "Output format: %d\n", gplot->outformat);
    fprintf(fp, "Title: %s\n", gplot->title);
    fprintf(fp, "X axis label: %s\n", gplot->xlabel);
    fprintf(fp, "Y axis label: %s\n", gplot->ylabel);

    fprintf(fp, "Commandfile name: %s\n", gplot->cmdname);
    fprintf(fp, "\nCommandfile data:");
    sarrayWriteStream(fp, gplot->cmddata);
    fprintf(fp, "\nDatafile names:");
    sarrayWriteStream(fp, gplot->datanames);
    fprintf(fp, "\nPlot data:");
    sarrayWriteStream(fp, gplot->plotdata);
    fprintf(fp, "\nPlot titles:");
    sarrayWriteStream(fp, gplot->plottitles);
    fprintf(fp, "\nPlot styles:");
    numaWriteStream(fp, gplot->plotstyles);

    fprintf(fp, "Number of plots: %d\n", gplot->nplots);
    fprintf(fp, "Output file name: %s\n", gplot->outname);
    fprintf(fp, "Axis scaling: %d\n", gplot->scaling);

    fclose(fp);
    return 0;
}
