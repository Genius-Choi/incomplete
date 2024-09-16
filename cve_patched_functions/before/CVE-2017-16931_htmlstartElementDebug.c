htmlstartElementDebug(void *ctx ATTRIBUTE_UNUSED, const xmlChar *name, const xmlChar **atts)
{
    int i;

    fprintf(SAXdebug, "SAX.startElement(%s", (char *) name);
    if (atts != NULL) {
        for (i = 0;(atts[i] != NULL);i++) {
	    fprintf(SAXdebug, ", %s", atts[i++]);
	    if (atts[i] != NULL) {
		unsigned char output[40];
		const unsigned char *att = atts[i];
		int outlen, attlen;
	        fprintf(SAXdebug, "='");
		while ((attlen = strlen((char*)att)) > 0) {
		    outlen = sizeof output - 1;
		    htmlEncodeEntities(output, &outlen, att, &attlen, '\'');
		    output[outlen] = 0;
		    fprintf(SAXdebug, "%s", (char *) output);
		    att += attlen;
		}
		fprintf(SAXdebug, "'");
	    }
	}
    }
    fprintf(SAXdebug, ")\n");
}
