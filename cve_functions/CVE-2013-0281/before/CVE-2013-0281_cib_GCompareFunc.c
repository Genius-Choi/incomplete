cib_GCompareFunc(gconstpointer a, gconstpointer b)
{
    const xmlNode *a_msg = a;
    const xmlNode *b_msg = b;

    int msg_a_id = 0;
    int msg_b_id = 0;
    const char *value = NULL;

    value = crm_element_value_const(a_msg, F_CIB_CALLID);
    msg_a_id = crm_parse_int(value, NULL);

    value = crm_element_value_const(b_msg, F_CIB_CALLID);
    msg_b_id = crm_parse_int(value, NULL);

    if (msg_a_id == msg_b_id) {
        return 0;
    } else if (msg_a_id < msg_b_id) {
        return -1;
    }
    return 1;
}
