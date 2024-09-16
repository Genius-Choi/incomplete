hasInternalSubsetDebug(void *ctx ATTRIBUTE_UNUSED)
{
    callbacks++;
    if (quiet)
	return(0);
    fprintf(SAXdebug, "SAX.hasInternalSubset()\n");
    return(0);
}
