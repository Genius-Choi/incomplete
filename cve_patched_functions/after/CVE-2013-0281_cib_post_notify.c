cib_post_notify(int options, const char *op, xmlNode * update,
                int result, xmlNode * new_obj)
{
    gboolean needed = FALSE;

    g_hash_table_foreach(client_list, need_post_notify, &needed);
    if (needed == FALSE) {
        return;
    }

    do_cib_notify(options, op, update, result, new_obj, T_CIB_UPDATE_CONFIRM);
}
