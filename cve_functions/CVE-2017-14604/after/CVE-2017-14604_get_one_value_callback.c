get_one_value_callback (gpointer key,
                        gpointer value,
                        gpointer callback_data)
{
    gpointer *returned_value;

    returned_value = callback_data;
    *returned_value = value;
}
