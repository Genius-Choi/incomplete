externalSubsetDebug(void *ctx ATTRIBUTE_UNUSED, const xmlChar *name,
	       const xmlChar *ExternalID, const xmlChar *SystemID)
{
    callbacks++;
    if (quiet)
	return;
    fprintf(SAXdebug, "SAX.externalSubset(%s,", name);
    if (ExternalID == NULL)
	fprintf(SAXdebug, " ,");
    else
	fprintf(SAXdebug, " %s,", ExternalID);
    if (SystemID == NULL)
	fprintf(SAXdebug, " )\n");
    else
	fprintf(SAXdebug, " %s)\n", SystemID);
}
