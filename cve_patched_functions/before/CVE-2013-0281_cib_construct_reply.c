cib_construct_reply(xmlNode * request, xmlNode * output, int rc)
{
    int lpc = 0;
    xmlNode *reply = NULL;
    const char *name = NULL;
    const char *value = NULL;

    const char *names[] = {
        F_CIB_OPERATION,
        F_CIB_CALLID,
        F_CIB_CLIENTID,
        F_CIB_CALLOPTS
    };
    static int max = DIMOF(names);

    crm_trace("Creating a basic reply");
    reply = create_xml_node(NULL, "cib-reply");
    crm_xml_add(reply, F_TYPE, T_CIB);

    for (lpc = 0; lpc < max; lpc++) {
        name = names[lpc];
        value = crm_element_value(request, name);
        crm_xml_add(reply, name, value);
    }

    crm_xml_add_int(reply, F_CIB_RC, rc);

    if (output != NULL) {
        crm_trace("Attaching reply output");
        add_message_xml(reply, F_CIB_CALLDATA, output);
    }
    return reply;
}
