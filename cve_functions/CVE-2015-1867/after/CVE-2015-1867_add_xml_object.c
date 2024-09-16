add_xml_object(xmlNode * parent, xmlNode * target, xmlNode * update, gboolean as_diff)
{
    xmlNode *a_child = NULL;
    const char *object_id = NULL;
    const char *object_name = NULL;

#if XML_PARSE_DEBUG
    crm_log_xml_trace("update:", update);
    crm_log_xml_trace("target:", target);
#endif

    CRM_CHECK(update != NULL, return 0);

    if (update->type == XML_COMMENT_NODE) {
        return add_xml_comment(parent, target, update);
    }

    object_name = crm_element_name(update);
    object_id = ID(update);

    CRM_CHECK(object_name != NULL, return 0);

    if (target == NULL && object_id == NULL) {
        /*  placeholder object */
        target = find_xml_node(parent, object_name, FALSE);

    } else if (target == NULL) {
        target = find_entity(parent, object_name, object_id);
    }

    if (target == NULL) {
        target = create_xml_node(parent, object_name);
        CRM_CHECK(target != NULL, return 0);
#if XML_PARSER_DEBUG
        crm_trace("Added  <%s%s%s/>", crm_str(object_name),
                  object_id ? " id=" : "", object_id ? object_id : "");

    } else {
        crm_trace("Found node <%s%s%s/> to update",
                  crm_str(object_name), object_id ? " id=" : "", object_id ? object_id : "");
#endif
    }

    CRM_CHECK(safe_str_eq(crm_element_name(target), crm_element_name(update)), return 0);

    if (as_diff == FALSE) {
        /* So that expand_plus_plus() gets called */
        copy_in_properties(target, update);

    } else {
        /* No need for expand_plus_plus(), just raw speed */
        xmlAttrPtr pIter = NULL;

        for (pIter = crm_first_attr(update); pIter != NULL; pIter = pIter->next) {
            const char *p_name = (const char *)pIter->name;
            const char *p_value = crm_attr_value(pIter);

            /* Remove it first so the ordering of the update is preserved */
            xmlUnsetProp(target, (const xmlChar *)p_name);
            xmlSetProp(target, (const xmlChar *)p_name, (const xmlChar *)p_value);
        }
    }

    for (a_child = __xml_first_child(update); a_child != NULL; a_child = __xml_next(a_child)) {
#if XML_PARSER_DEBUG
        crm_trace("Updating child <%s id=%s>", crm_element_name(a_child), ID(a_child));
#endif
        add_xml_object(target, NULL, a_child, as_diff);
    }

#if XML_PARSER_DEBUG
    crm_trace("Finished with <%s id=%s>", crm_str(object_name), crm_str(object_id));
#endif
    return 0;
}
