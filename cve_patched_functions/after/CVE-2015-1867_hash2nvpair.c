hash2nvpair(gpointer key, gpointer value, gpointer user_data)
{
    const char *name = key;
    const char *s_value = value;

    xmlNode *xml_node = user_data;
    xmlNode *xml_child = create_xml_node(xml_node, XML_CIB_TAG_NVPAIR);

    crm_xml_add(xml_child, XML_ATTR_ID, name);
    crm_xml_add(xml_child, XML_NVPAIR_ATTR_NAME, name);
    crm_xml_add(xml_child, XML_NVPAIR_ATTR_VALUE, s_value);

    crm_trace("dumped: name=%s value=%s", name, s_value);
}
