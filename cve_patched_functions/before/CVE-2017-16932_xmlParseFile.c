xmlParseFile(const char *filename) {
    return(xmlSAXParseFile(NULL, filename, 0));
}
