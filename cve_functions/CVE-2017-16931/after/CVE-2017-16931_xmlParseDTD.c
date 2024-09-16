xmlParseDTD(const xmlChar *ExternalID, const xmlChar *SystemID) {
    return(xmlSAXParseDTD(NULL, ExternalID, SystemID));
}
