ofproto_set_mac_table_config(struct ofproto *ofproto, unsigned idle_time,
                             size_t max_entries)
{
    if (ofproto->ofproto_class->set_mac_table_config) {
        ofproto->ofproto_class->set_mac_table_config(ofproto, idle_time,
                                                     max_entries);
    }
}
