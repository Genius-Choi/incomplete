elementDeclDebug(void *ctx ATTRIBUTE_UNUSED, const xmlChar *name, int type,
	    xmlElementContentPtr content ATTRIBUTE_UNUSED)
{
    callbacks++;
    if (quiet)
	return;
    fprintf(SAXdebug, "SAX.elementDecl(%s, %d, ...)\n",
            name, type);
}
