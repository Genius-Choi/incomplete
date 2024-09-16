cib_replace_notify(const char *origin, xmlNode * update, int result, xmlNode * diff)
{
    xmlNode *replace_msg = NULL;

    int add_updates = 0;
    int add_epoch = 0;
    int add_admin_epoch = 0;

    int del_updates = 0;
    int del_epoch = 0;
    int del_admin_epoch = 0;

    if (diff == NULL) {
        return;
    }

    cib_diff_version_details(diff, &add_admin_epoch, &add_epoch, &add_updates,
                             &del_admin_epoch, &del_epoch, &del_updates);

    if(del_updates < 0) {
        crm_log_xml_debug(diff, "Bad replace diff");
    }

    if (add_updates != del_updates) {
        crm_info("Replaced: %d.%d.%d -> %d.%d.%d from %s",
                 del_admin_epoch, del_epoch, del_updates,
                 add_admin_epoch, add_epoch, add_updates, crm_str(origin));
    } else if (diff != NULL) {
        crm_info("Local-only Replace: %d.%d.%d from %s",
                 add_admin_epoch, add_epoch, add_updates, crm_str(origin));
    }

    replace_msg = create_xml_node(NULL, "notify-replace");
    crm_xml_add(replace_msg, F_TYPE, T_CIB_NOTIFY);
    crm_xml_add(replace_msg, F_SUBTYPE, T_CIB_REPLACE_NOTIFY);
    crm_xml_add(replace_msg, F_CIB_OPERATION, CIB_OP_REPLACE);
    crm_xml_add_int(replace_msg, F_CIB_RC, result);
    attach_cib_generation(replace_msg, "cib-replace-generation", update);

    crm_log_xml_trace(replace_msg, "CIB Replaced");

    g_hash_table_foreach_remove(client_list, cib_notify_client, replace_msg);
    free_xml(replace_msg);
}
