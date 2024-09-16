format_CONTROLLER(const struct ofpact_controller *a, struct ds *s)
{
    if (a->reason == OFPR_ACTION && !a->controller_id && !a->userdata_len
        && !a->pause) {
        ds_put_format(s, "%sCONTROLLER:%s%"PRIu16,
                      colors.special, colors.end, a->max_len);
    } else {
        enum ofp_packet_in_reason reason = a->reason;

        ds_put_format(s, "%scontroller(%s", colors.paren, colors.end);
        if (reason != OFPR_ACTION) {
            char reasonbuf[OFPUTIL_PACKET_IN_REASON_BUFSIZE];

            ds_put_format(s, "%sreason=%s%s,", colors.param, colors.end,
                          ofputil_packet_in_reason_to_string(
                              reason, reasonbuf, sizeof reasonbuf));
        }
        if (a->max_len != UINT16_MAX) {
            ds_put_format(s, "%smax_len=%s%"PRIu16",",
                          colors.param, colors.end, a->max_len);
        }
        if (a->controller_id != 0) {
            ds_put_format(s, "%sid=%s%"PRIu16",",
                          colors.param, colors.end, a->controller_id);
        }
        if (a->userdata_len) {
            ds_put_format(s, "%suserdata=%s", colors.param, colors.end);
            format_hex_arg(s, a->userdata, a->userdata_len);
            ds_put_char(s, ',');
        }
        if (a->pause) {
            ds_put_format(s, "%spause%s,", colors.value, colors.end);
        }
        ds_chomp(s, ',');
        ds_put_format(s, "%s)%s", colors.paren, colors.end);
    }
}
