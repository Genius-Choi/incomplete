pcmkRegisterNode(xmlNodePtr node)
{
    xml_private_t *p = NULL;

    switch(node->type) {
        case XML_ELEMENT_NODE:
        case XML_DOCUMENT_NODE:
        case XML_ATTRIBUTE_NODE:
        case XML_COMMENT_NODE:
            p = calloc(1, sizeof(xml_private_t));
            p->check = XML_PRIVATE_MAGIC;
            /* Flags will be reset if necessary when tracking is enabled */
            p->flags |= (xpf_dirty|xpf_created);
            node->_private = p;
            break;
        case XML_TEXT_NODE:
        case XML_DTD_NODE:
            break;
        default:
            /* Ignore */
            crm_trace("Ignoring %p %d", node, node->type);
            CRM_LOG_ASSERT(node->type == XML_ELEMENT_NODE);
            break;
    }

    if(p && TRACKING_CHANGES(node)) {
        /* XML_ELEMENT_NODE doesn't get picked up here, node->doc is
         * not hooked up at the point we are called
         */
        set_doc_flag(node, xpf_dirty);
        __xml_node_dirty(node);
    }
}
