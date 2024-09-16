static gint find_by_button(gconstpointer a, gconstpointer button)
{
    const event_gui_data_t *evdata = a;
    return (evdata->toggle_button != button);
}
