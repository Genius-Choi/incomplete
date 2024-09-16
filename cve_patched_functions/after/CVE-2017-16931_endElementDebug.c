endElementDebug(void *ctx ATTRIBUTE_UNUSED, const xmlChar *name)
{
    callbacks++;
    if (quiet)
	return;
    fprintf(SAXdebug, "SAX.endElement(%s)\n", (char *) name);
}
