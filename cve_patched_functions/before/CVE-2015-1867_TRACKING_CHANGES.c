static inline bool TRACKING_CHANGES(xmlNode *xml)
{
    if(xml == NULL || xml->doc == NULL || xml->doc->_private == NULL) {
        return FALSE;
    } else if(is_set(((xml_private_t *)xml->doc->_private)->flags, xpf_tracking)) {
        return TRUE;
    }
    return FALSE;
}
