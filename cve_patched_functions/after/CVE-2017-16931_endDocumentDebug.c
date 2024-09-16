endDocumentDebug(void *ctx ATTRIBUTE_UNUSED)
{
    callbacks++;
    if (quiet)
	return;
    fprintf(SAXdebug, "SAX.endDocument()\n");
}
