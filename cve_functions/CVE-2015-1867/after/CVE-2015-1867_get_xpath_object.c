get_xpath_object(const char *xpath, xmlNode * xml_obj, int error_level)
{
    int max;
    xmlNode *result = NULL;
    xmlXPathObjectPtr xpathObj = NULL;
    char *nodePath = NULL;
    char *matchNodePath = NULL;

    if (xpath == NULL) {
        return xml_obj;         /* or return NULL? */
    }

    xpathObj = xpath_search(xml_obj, xpath);
    nodePath = (char *)xmlGetNodePath(xml_obj);
    max = numXpathResults(xpathObj);

    if (max < 1) {
        do_crm_log(error_level, "No match for %s in %s", xpath, crm_str(nodePath));
        crm_log_xml_explicit(xml_obj, "Unexpected Input");

    } else if (max > 1) {
        int lpc = 0;

        do_crm_log(error_level, "Too many matches for %s in %s", xpath, crm_str(nodePath));

        for (lpc = 0; lpc < max; lpc++) {
            xmlNode *match = getXpathResult(xpathObj, lpc);

            CRM_LOG_ASSERT(match != NULL);
            if(match != NULL) {
                matchNodePath = (char *)xmlGetNodePath(match);
                do_crm_log(error_level, "%s[%d] = %s", xpath, lpc, crm_str(matchNodePath));
                free(matchNodePath);
            }
        }
        crm_log_xml_explicit(xml_obj, "Bad Input");

    } else {
        result = getXpathResult(xpathObj, 0);
    }

    freeXpathObject(xpathObj);
    free(nodePath);

    return result;
}
