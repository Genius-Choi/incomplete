static int FLTIsGMLDefaultProperty(const char* pszName)
{
    return (strcmp(pszName, "gml:name") == 0 ||
            strcmp(pszName, "gml:description") == 0 ||
            strcmp(pszName, "gml:descriptionReference") == 0 ||
            strcmp(pszName, "gml:identifier") == 0 ||
            strcmp(pszName, "gml:boundedBy") == 0 ||
            strcmp(pszName, "@gml:id") == 0);
}
