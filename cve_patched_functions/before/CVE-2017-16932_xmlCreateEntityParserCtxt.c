xmlCreateEntityParserCtxt(const xmlChar *URL, const xmlChar *ID,
	                  const xmlChar *base) {
    return xmlCreateEntityParserCtxtInternal(URL, ID, base, NULL);

}
