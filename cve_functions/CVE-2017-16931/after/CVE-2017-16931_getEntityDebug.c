getEntityDebug(void *ctx ATTRIBUTE_UNUSED, const xmlChar *name)
{
    callbacks++;
    if (quiet)
	return(NULL);
    fprintf(SAXdebug, "SAX.getEntity(%s)\n", name);
    return(NULL);
}
