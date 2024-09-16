HandleMessage(HANDLE pipe, DWORD bytes, DWORD count, LPHANDLE events, undo_lists_t *lists)
{
    DWORD read;
    union {
        message_header_t header;
        address_message_t address;
        route_message_t route;
        flush_neighbors_message_t flush_neighbors;
        block_dns_message_t block_dns;
        dns_cfg_message_t dns;
    } msg;
    ack_message_t ack = {
        .header = {
            .type = msg_acknowledgement,
            .size = sizeof(ack),
            .message_id = -1
        },
        .error_number = ERROR_MESSAGE_DATA
    };

    read = ReadPipeAsync(pipe, &msg, bytes, count, events);
    if (read != bytes || read < sizeof(msg.header) || read != msg.header.size)
    {
        goto out;
    }

    ack.header.message_id = msg.header.message_id;

    switch (msg.header.type)
    {
        case msg_add_address:
        case msg_del_address:
            if (msg.header.size == sizeof(msg.address))
            {
                ack.error_number = HandleAddressMessage(&msg.address, lists);
            }
            break;

        case msg_add_route:
        case msg_del_route:
            if (msg.header.size == sizeof(msg.route))
            {
                ack.error_number = HandleRouteMessage(&msg.route, lists);
            }
            break;

        case msg_flush_neighbors:
            if (msg.header.size == sizeof(msg.flush_neighbors))
            {
                ack.error_number = HandleFlushNeighborsMessage(&msg.flush_neighbors);
            }
            break;

        case msg_add_block_dns:
        case msg_del_block_dns:
            if (msg.header.size == sizeof(msg.block_dns))
            {
                ack.error_number = HandleBlockDNSMessage(&msg.block_dns, lists);
            }
            break;

        case msg_register_dns:
            ack.error_number = HandleRegisterDNSMessage();
            break;

        case msg_add_dns_cfg:
        case msg_del_dns_cfg:
            ack.error_number = HandleDNSConfigMessage(&msg.dns, lists);
            break;

        default:
            ack.error_number = ERROR_MESSAGE_TYPE;
            MsgToEventLog(MSG_FLAGS_ERROR, TEXT("Unknown message type %d"), msg.header.type);
            break;
    }

out:
    WritePipeAsync(pipe, &ack, sizeof(ack), count, events);
}
