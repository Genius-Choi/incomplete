processingInstructionDebug(void *ctx ATTRIBUTE_UNUSED, const xmlChar *target,
                      const xmlChar *data)
{
    callbacks++;
    if (quiet)
	return;
    if (data != NULL)
	fprintf(SAXdebug, "SAX.processingInstruction(%s, %s)\n",
		(char *) target, (char *) data);
    else
	fprintf(SAXdebug, "SAX.processingInstruction(%s, NULL)\n",
		(char *) target);
}
