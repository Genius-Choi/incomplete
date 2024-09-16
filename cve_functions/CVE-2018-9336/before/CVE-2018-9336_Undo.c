Undo(undo_lists_t *lists)
{
    undo_type_t type;
    block_dns_data_t *interface_data;
    for (type = 0; type < _undo_type_max; type++)
    {
        list_item_t **pnext = &(*lists)[type];
        while (*pnext)
        {
            list_item_t *item = *pnext;
            switch (type)
            {
                case address:
                    DeleteAddress(item->data);
                    break;

                case route:
                    DeleteRoute(item->data);
                    break;

                case undo_dns4:
                    DeleteDNS(AF_INET, item->data);
                    break;

                case undo_dns6:
                    DeleteDNS(AF_INET6, item->data);
                    break;

                case block_dns:
                    interface_data = (block_dns_data_t*)(item->data);
                    delete_block_dns_filters(interface_data->engine);
                    if (interface_data->metric_v4 >= 0)
                    {
                        set_interface_metric(interface_data->index, AF_INET,
                                             interface_data->metric_v4);
                    }
                    if (interface_data->metric_v6 >= 0)
                    {
                        set_interface_metric(interface_data->index, AF_INET6,
                                             interface_data->metric_v6);
                    }
                    break;
            }

            /* Remove from the list and free memory */
            *pnext = item->next;
            free(item->data);
            free(item);
        }
    }
}
