do_cib_notify(int options, const char *op, xmlNode * update,
              int result, xmlNode * result_data, const char *msg_type)
{
    xmlNode *update_msg = NULL;
    const char *id = NULL;

    update_msg = create_xml_node(NULL, "notify");

    if (result_data != NULL) {
        id = crm_element_value(result_data, XML_ATTR_ID);
    }

    crm_xml_add(update_msg, F_TYPE, T_CIB_NOTIFY);
    crm_xml_add(update_msg, F_SUBTYPE, msg_type);
    crm_xml_add(update_msg, F_CIB_OPERATION, op);
    crm_xml_add_int(update_msg, F_CIB_RC, result);

    if (id != NULL) {
        crm_xml_add(update_msg, F_CIB_OBJID, id);
    }

    if (update != NULL) {
        crm_trace("Setting type to update->name: %s", crm_element_name(update));
        crm_xml_add(update_msg, F_CIB_OBJTYPE, crm_element_name(update));

    } else if (result_data != NULL) {
        crm_trace("Setting type to new_obj->name: %s", crm_element_name(result_data));
        crm_xml_add(update_msg, F_CIB_OBJTYPE, crm_element_name(result_data));

    } else {
        crm_trace("Not Setting type");
    }

    attach_cib_generation(update_msg, "cib_generation", the_cib);
    if (update != NULL) {
        add_message_xml(update_msg, F_CIB_UPDATE, update);
    }
    if (result_data != NULL) {
        add_message_xml(update_msg, F_CIB_UPDATE_RESULT, result_data);
    }

    crm_trace("Notifying clients");
    g_hash_table_foreach_remove(client_list, cib_notify_client, update_msg);
    free_xml(update_msg);
    crm_trace("Notify complete");
}
