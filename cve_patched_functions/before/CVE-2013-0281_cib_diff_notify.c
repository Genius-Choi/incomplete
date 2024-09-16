cib_diff_notify(int options, const char *client, const char *call_id, const char *op,
                xmlNode * update, int result, xmlNode * diff)
{
    int add_updates = 0;
    int add_epoch = 0;
    int add_admin_epoch = 0;

    int del_updates = 0;
    int del_epoch = 0;
    int del_admin_epoch = 0;

    int log_level = LOG_DEBUG_2;

    if (diff == NULL) {
        return;
    }

    if (result != pcmk_ok) {
        log_level = LOG_WARNING;
    }

    cib_diff_version_details(diff, &add_admin_epoch, &add_epoch, &add_updates,
                             &del_admin_epoch, &del_epoch, &del_updates);

    if (add_updates != del_updates) {
        do_crm_log(log_level,
                   "Update (client: %s%s%s): %d.%d.%d -> %d.%d.%d (%s)",
                   client, call_id ? ", call:" : "", call_id ? call_id : "",
                   del_admin_epoch, del_epoch, del_updates,
                   add_admin_epoch, add_epoch, add_updates, pcmk_strerror(result));

    } else if (diff != NULL) {
        do_crm_log(log_level,
                   "Local-only Change (client:%s%s%s): %d.%d.%d (%s)",
                   client, call_id ? ", call: " : "", call_id ? call_id : "",
                   add_admin_epoch, add_epoch, add_updates, pcmk_strerror(result));
    }

    do_cib_notify(options, op, update, result, diff, T_CIB_DIFF_NOTIFY);
}
