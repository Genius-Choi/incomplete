print_simple_status(pe_working_set_t * data_set)
{
    node_t *dc = NULL;
    GListPtr gIter = NULL;
    int nodes_online = 0;
    int nodes_standby = 0;

    dc = data_set->dc_node;

    if (dc == NULL) {
        mon_warn("No DC ");
    }

    for (gIter = data_set->nodes; gIter != NULL; gIter = gIter->next) {
        node_t *node = (node_t *) gIter->data;

        if (node->details->standby && node->details->online) {
            nodes_standby++;
        } else if (node->details->online) {
            nodes_online++;
        } else {
            mon_warn("offline node: %s", node->details->uname);
        }
    }

    if (!has_warnings) {
        print_as("Ok: %d nodes online", nodes_online);
        if (nodes_standby > 0) {
            print_as(", %d standby nodes", nodes_standby);
        }
        print_as(", %d resources configured", count_resources(data_set, NULL));
    }

    print_as("\n");
    return 0;
}
