__xml_accept_changes(xmlNode * xml)
{
    xmlNode *cIter = NULL;
    xmlAttr *pIter = NULL;
    xml_private_t *p = xml->_private;

    p->flags = xpf_none;
    pIter = crm_first_attr(xml);

    while (pIter != NULL) {
        const xmlChar *name = pIter->name;

        p = pIter->_private;
        pIter = pIter->next;

        if(p->flags & xpf_deleted) {
            xml_remove_prop(xml, (const char *)name);

        } else {
            p->flags = xpf_none;
        }
    }

    for (cIter = __xml_first_child(xml); cIter != NULL; cIter = __xml_next(cIter)) {
        __xml_accept_changes(cIter);
    }
}
