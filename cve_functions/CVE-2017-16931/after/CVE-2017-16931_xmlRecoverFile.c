xmlRecoverFile(const char *filename) {
    return(xmlSAXParseFile(NULL, filename, 1));
}
