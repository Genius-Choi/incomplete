startElementNsDebug(void *ctx ATTRIBUTE_UNUSED,
                    const xmlChar *localname,
                    const xmlChar *prefix,
                    const xmlChar *URI,
		    int nb_namespaces,
		    const xmlChar **namespaces,
		    int nb_attributes,
		    int nb_defaulted,
		    const xmlChar **attributes)
{
    int i;

    callbacks++;
    if (quiet)
	return;
    fprintf(SAXdebug, "SAX.startElementNs(%s", (char *) localname);
    if (prefix == NULL)
	fprintf(SAXdebug, ", NULL");
    else
	fprintf(SAXdebug, ", %s", (char *) prefix);
    if (URI == NULL)
	fprintf(SAXdebug, ", NULL");
    else
	fprintf(SAXdebug, ", '%s'", (char *) URI);
    fprintf(SAXdebug, ", %d", nb_namespaces);

    if (namespaces != NULL) {
        for (i = 0;i < nb_namespaces * 2;i++) {
	    fprintf(SAXdebug, ", xmlns");
	    if (namespaces[i] != NULL)
	        fprintf(SAXdebug, ":%s", namespaces[i]);
	    i++;
	    fprintf(SAXdebug, "='%s'", namespaces[i]);
	}
    }
    fprintf(SAXdebug, ", %d, %d", nb_attributes, nb_defaulted);
    if (attributes != NULL) {
        for (i = 0;i < nb_attributes * 5;i += 5) {
	    if (attributes[i + 1] != NULL)
		fprintf(SAXdebug, ", %s:%s='", attributes[i + 1], attributes[i]);
	    else
		fprintf(SAXdebug, ", %s='", attributes[i]);
	    fprintf(SAXdebug, "%.4s...', %d", attributes[i + 3],
		    (int)(attributes[i + 4] - attributes[i + 3]));
	}
    }
    fprintf(SAXdebug, ")\n");
}
