urip_checkURL(const char *URL) {
    xmlDocPtr doc;

    doc = xmlReadFile(URL, NULL, 0);
    if (doc == NULL)
        return(-1);
    xmlFreeDoc(doc);
    return(1);
}
