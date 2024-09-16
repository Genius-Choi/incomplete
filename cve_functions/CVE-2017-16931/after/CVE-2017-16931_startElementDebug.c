startElementDebug(void *ctx ATTRIBUTE_UNUSED, const xmlChar *name, const xmlChar **atts)
{
    int i;

    callbacks++;
    if (quiet)
	return;
    fprintf(SAXdebug, "SAX.startElement(%s", (char *) name);
    if (atts != NULL) {
        for (i = 0;(atts[i] != NULL);i++) {
	    fprintf(SAXdebug, ", %s='", atts[i++]);
	    if (atts[i] != NULL)
	        fprintf(SAXdebug, "%s'", atts[i]);
	}
    }
    fprintf(SAXdebug, ")\n");
}
