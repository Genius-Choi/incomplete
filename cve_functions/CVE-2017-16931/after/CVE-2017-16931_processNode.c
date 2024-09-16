static void processNode(FILE *out, xmlTextReaderPtr reader) {
    const xmlChar *name, *value;
    int type, empty;

    type = xmlTextReaderNodeType(reader);
    empty = xmlTextReaderIsEmptyElement(reader);

    name = xmlTextReaderConstName(reader);
    if (name == NULL)
	name = BAD_CAST "--";

    value = xmlTextReaderConstValue(reader);


    fprintf(out, "%d %d %s %d %d",
	    xmlTextReaderDepth(reader),
	    type,
	    name,
	    empty,
	    xmlTextReaderHasValue(reader));
    if (value == NULL)
	fprintf(out, "\n");
    else {
	fprintf(out, " %s\n", value);
    }
}
