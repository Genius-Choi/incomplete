xmlParseDoc(const xmlChar *cur) {
    return(xmlSAXParseDoc(NULL, cur, 0));
}
