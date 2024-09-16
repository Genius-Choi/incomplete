cdataBlockDebug(void *ctx ATTRIBUTE_UNUSED, const xmlChar *value, int len)
{
    callbacks++;
    if (quiet)
	return;
    fprintf(SAXdebug, "SAX.pcdata(%.20s, %d)\n",
	    (char *) value, len);
}
