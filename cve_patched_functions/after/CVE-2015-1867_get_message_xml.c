get_message_xml(xmlNode * msg, const char *field)
{
    xmlNode *tmp = first_named_child(msg, field);

    return __xml_first_child(tmp);
}
