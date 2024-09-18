gio_read_socket (GIOChannel *gio, GIOCondition condition, gpointer data)
{
    struct gio_to_qb_poll *adaptor = (struct gio_to_qb_poll *)data;
    gint fd = g_io_channel_unix_get_fd(gio);

    crm_trace("%p.%d %d (ref=%d)", data, fd, condition, gio_adapter_refcount(adaptor));

    if(condition & G_IO_NVAL) {
        crm_trace("Marking failed adaptor %p unused", adaptor);
        adaptor->is_used = QB_FALSE;
    }

    return (adaptor->fn(fd, condition, adaptor->data) == 0);
}
