HandleAddressMessage(address_message_t *msg, undo_lists_t *lists)
{
    DWORD err;
    PMIB_UNICASTIPADDRESS_ROW addr_row;
    BOOL add = msg->header.type == msg_add_address;

    addr_row = malloc(sizeof(*addr_row));
    if (addr_row == NULL)
    {
        return ERROR_OUTOFMEMORY;
    }

    InitializeUnicastIpAddressEntry(addr_row);
    addr_row->Address = sockaddr_inet(msg->family, &msg->address);
    addr_row->OnLinkPrefixLength = (UINT8) msg->prefix_len;

    if (msg->iface.index != -1)
    {
        addr_row->InterfaceIndex = msg->iface.index;
    }
    else
    {
        NET_LUID luid;
        err = InterfaceLuid(msg->iface.name, &luid);
        if (err)
        {
            goto out;
        }
        addr_row->InterfaceLuid = luid;
    }

    if (add)
    {
        err = CreateUnicastIpAddressEntry(addr_row);
        if (err)
        {
            goto out;
        }

        err = AddListItem(&(*lists)[address], addr_row);
        if (err)
        {
            DeleteAddress(addr_row);
        }
    }
    else
    {
        err = DeleteAddress(addr_row);
        if (err)
        {
            goto out;
        }

        free(RemoveListItem(&(*lists)[address], CmpAddress, addr_row));
    }

out:
    if (!add || err)
    {
        free(addr_row);
    }

    return err;
}
