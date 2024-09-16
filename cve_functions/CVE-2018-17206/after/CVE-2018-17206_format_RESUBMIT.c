format_RESUBMIT(const struct ofpact_resubmit *a, struct ds *s)
{
    if (a->in_port != OFPP_IN_PORT && a->table_id == 255) {
        ds_put_format(s, "%sresubmit:%s", colors.special, colors.end);
        ofputil_format_port(a->in_port, s);
    } else {
        ds_put_format(s, "%sresubmit(%s", colors.paren, colors.end);
        if (a->in_port != OFPP_IN_PORT) {
            ofputil_format_port(a->in_port, s);
        }
        ds_put_char(s, ',');
        if (a->table_id != 255) {
            ds_put_format(s, "%"PRIu8, a->table_id);
        }
        ds_put_format(s, "%s)%s", colors.paren, colors.end);
    }
}
