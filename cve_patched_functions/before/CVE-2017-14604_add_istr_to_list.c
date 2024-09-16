add_istr_to_list (gpointer key,
                  gpointer value,
                  gpointer callback_data)
{
    GList **list;

    list = callback_data;
    *list = g_list_prepend (*list, g_strdup (key));
}
