print_node_attribute(gpointer name, gpointer node_data)
{
    const char *value = NULL;
    node_t *node = (node_t *) node_data;

    value = g_hash_table_lookup(node->details->attrs, name);
    print_as("    + %-32s\t: %-10s", (char *)name, value);
    print_attr_msg(node, node->details->running_rsc, name, value);
    print_as("\n");
}
