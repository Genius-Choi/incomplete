hasExternalSubsetDebug(void *ctx ATTRIBUTE_UNUSED)
{
    callbacks++;
    if (quiet)
	return(0);
    fprintf(SAXdebug, "SAX.hasExternalSubset()\n");
    return(0);
}
