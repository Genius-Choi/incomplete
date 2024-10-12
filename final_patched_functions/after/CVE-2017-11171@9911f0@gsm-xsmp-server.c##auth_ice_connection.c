auth_ice_connection (IceConn ice_conn)
{
        GIOChannel            *channel;
        GsmIceConnectionWatch *data;
        int                    fd;

        g_debug ("GsmXsmpServer: auth_ice_connection()");

        fd = IceConnectionNumber (ice_conn);
        fcntl (fd, F_SETFD, fcntl (fd, F_GETFD, 0) | FD_CLOEXEC);
        channel = g_io_channel_unix_new (fd);

        data = g_new0 (GsmIceConnectionWatch, 1);
        ice_conn->context = data;

        data->protocol_timeout = g_timeout_add_seconds (5,
                                                        (GSourceFunc)ice_protocol_timeout,
                                                        ice_conn);
        data->watch_id = g_io_add_watch (channel,
                                         G_IO_IN | G_IO_ERR,
                                         (GIOFunc)auth_iochannel_watch,
                                         ice_conn);
        g_io_channel_unref (channel);
}
