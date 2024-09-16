getParameterEntityDebug(void *ctx ATTRIBUTE_UNUSED, const xmlChar *name)
{
    callbacks++;
    if (quiet)
	return(NULL);
    fprintf(SAXdebug, "SAX.getParameterEntity(%s)\n", name);
    return(NULL);
}
