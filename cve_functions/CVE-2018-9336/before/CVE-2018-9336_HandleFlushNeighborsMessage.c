HandleFlushNeighborsMessage(flush_neighbors_message_t *msg)
{
    if (msg->family == AF_INET)
    {
        return FlushIpNetTable(msg->iface.index);
    }

    return FlushIpNetTable2(msg->family, msg->iface.index);
}
