__xml_build_changes(xmlNode * xml, xmlNode *patchset)
{
    xmlNode *cIter = NULL;
    xmlAttr *pIter = NULL;
    xmlNode *change = NULL;
    xml_private_t *p = xml->_private;

    if(patchset && is_set(p->flags, xpf_created)) {
        int offset = 0;
        char buffer[XML_BUFFER_SIZE];

        if(__get_prefix(NULL, xml->parent, buffer, offset) > 0) {
            int position = __xml_offset_no_deletions(xml);

            change = create_xml_node(patchset, XML_DIFF_CHANGE);

            crm_xml_add(change, XML_DIFF_OP, "create");
            crm_xml_add(change, XML_DIFF_PATH, buffer);
            crm_xml_add_int(change, XML_DIFF_POSITION, position);
            add_node_copy(change, xml);
        }

        return;
    }

    for (pIter = crm_first_attr(xml); pIter != NULL; pIter = pIter->next) {
        xmlNode *attr = NULL;

        p = pIter->_private;
        if(is_not_set(p->flags, xpf_deleted) && is_not_set(p->flags, xpf_dirty)) {
            continue;
        }

        if(change == NULL) {
            int offset = 0;
            char buffer[XML_BUFFER_SIZE];

            if(__get_prefix(NULL, xml, buffer, offset) > 0) {
                change = create_xml_node(patchset, XML_DIFF_CHANGE);

                crm_xml_add(change, XML_DIFF_OP, "modify");
                crm_xml_add(change, XML_DIFF_PATH, buffer);

                change = create_xml_node(change, XML_DIFF_LIST);
            }
        }

        attr = create_xml_node(change, XML_DIFF_ATTR);

        crm_xml_add(attr, XML_NVPAIR_ATTR_NAME, (const char *)pIter->name);
        if(p->flags & xpf_deleted) {
            crm_xml_add(attr, XML_DIFF_OP, "unset");

        } else {
            const char *value = crm_element_value(xml, (const char *)pIter->name);

            crm_xml_add(attr, XML_DIFF_OP, "set");
            crm_xml_add(attr, XML_NVPAIR_ATTR_VALUE, value);
        }
    }

    if(change) {
        xmlNode *result = NULL;

        change = create_xml_node(change->parent, XML_DIFF_RESULT);
        result = create_xml_node(change, (const char *)xml->name);

        for (pIter = crm_first_attr(xml); pIter != NULL; pIter = pIter->next) {
            const char *value = crm_element_value(xml, (const char *)pIter->name);

            p = pIter->_private;
            if (is_not_set(p->flags, xpf_deleted)) {
                crm_xml_add(result, (const char *)pIter->name, value);
            }
        }
    }

    for (cIter = __xml_first_child(xml); cIter != NULL; cIter = __xml_next(cIter)) {
        __xml_build_changes(cIter, patchset);
    }

    p = xml->_private;
    if(patchset && is_set(p->flags, xpf_moved)) {
        int offset = 0;
        char buffer[XML_BUFFER_SIZE];

        crm_trace("%s.%s moved to position %d", xml->name, ID(xml), __xml_offset(xml));
        if(__get_prefix(NULL, xml, buffer, offset) > 0) {
            change = create_xml_node(patchset, XML_DIFF_CHANGE);

            crm_xml_add(change, XML_DIFF_OP, "move");
            crm_xml_add(change, XML_DIFF_PATH, buffer);
            crm_xml_add_int(change, XML_DIFF_POSITION, __xml_offset_no_deletions(xml));
        }
    }
}
