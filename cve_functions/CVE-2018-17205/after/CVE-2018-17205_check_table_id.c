check_table_id(const struct ofproto *ofproto, uint8_t table_id)
{
    return table_id == OFPTT_ALL || table_id < ofproto->n_tables;
}
