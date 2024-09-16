attach_cib_generation(xmlNode * msg, const char *field, xmlNode * a_cib)
{
    xmlNode *generation = create_xml_node(NULL, XML_CIB_TAG_GENERATION_TUPPLE);

    if (a_cib != NULL) {
        copy_in_properties(generation, a_cib);
    }
    add_message_xml(msg, field, generation);
    free_xml(generation);
}
