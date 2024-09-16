referenceDebug(void *ctx ATTRIBUTE_UNUSED, const xmlChar *name)
{
    callbacks++;
    if (quiet)
	return;
    fprintf(SAXdebug, "SAX.reference(%s)\n", name);
}
