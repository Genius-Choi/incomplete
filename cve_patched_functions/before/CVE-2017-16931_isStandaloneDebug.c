isStandaloneDebug(void *ctx ATTRIBUTE_UNUSED)
{
    callbacks++;
    if (quiet)
	return(0);
    fprintf(SAXdebug, "SAX.isStandalone()\n");
    return(0);
}
