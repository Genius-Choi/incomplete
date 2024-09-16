endElementNsDebug(void *ctx ATTRIBUTE_UNUSED,
                  const xmlChar *localname,
                  const xmlChar *prefix,
                  const xmlChar *URI)
{
    callbacks++;
    if (quiet)
	return;
    fprintf(SAXdebug, "SAX.endElementNs(%s", (char *) localname);
    if (prefix == NULL)
	fprintf(SAXdebug, ", NULL");
    else
	fprintf(SAXdebug, ", %s", (char *) prefix);
    if (URI == NULL)
	fprintf(SAXdebug, ", NULL)\n");
    else
	fprintf(SAXdebug, ", '%s')\n", (char *) URI);
}
