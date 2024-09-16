ptaaRead(const char  *filename)
{
FILE  *fp;
PTAA  *ptaa;

    PROCNAME("ptaaRead");

    if (!filename)
        return (PTAA *)ERROR_PTR("filename not defined", procName, NULL);

    if ((fp = fopenReadStream(filename)) == NULL)
        return (PTAA *)ERROR_PTR("stream not opened", procName, NULL);
    ptaa = ptaaReadStream(fp);
    fclose(fp);
    if (!ptaa)
        return (PTAA *)ERROR_PTR("ptaa not read", procName, NULL);
    return ptaa;
}
