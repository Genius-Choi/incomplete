query_table_desc__(struct ofputil_table_desc *td,
                   struct ofproto *ofproto, uint8_t table_id)
{
    const struct oftable *t = &ofproto->tables[table_id];

    td->table_id = table_id;
    td->eviction = (t->eviction & EVICTION_OPENFLOW
                    ? OFPUTIL_TABLE_EVICTION_ON
                    : OFPUTIL_TABLE_EVICTION_OFF);
    td->eviction_flags = OFPROTO_EVICTION_FLAGS;
    td->vacancy = (t->vacancy_event
                   ? OFPUTIL_TABLE_VACANCY_ON
                   : OFPUTIL_TABLE_VACANCY_OFF);
    td->table_vacancy.vacancy_down = t->vacancy_down;
    td->table_vacancy.vacancy_up = t->vacancy_up;
    td->table_vacancy.vacancy = oftable_vacancy(t);
}
