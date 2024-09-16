getCodePage(void)
{
    unsigned long CpList[8], CpSize;

    if (!getenv("WINDOWID") && !DosQueryCp(sizeof(CpList), CpList, &CpSize))
	return Sprintf("CP%d", *CpList)->ptr;
    return NULL;
}
