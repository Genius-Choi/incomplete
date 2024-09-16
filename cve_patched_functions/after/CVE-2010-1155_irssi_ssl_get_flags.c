static GIOFlags irssi_ssl_get_flags(GIOChannel *handle)
{
    GIOSSLChannel *chan = (GIOSSLChannel *)handle;

    return chan->giochan->funcs->io_get_flags(handle);
}
