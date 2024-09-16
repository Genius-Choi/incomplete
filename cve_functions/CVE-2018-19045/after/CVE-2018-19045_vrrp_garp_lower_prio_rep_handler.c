vrrp_garp_lower_prio_rep_handler(vector_t *strvec)
{
	unsigned garp_lower_prio_rep;

        if (!read_unsigned_strvec(strvec, 1, &garp_lower_prio_rep, 0, INT_MAX, true)) {
                report_config_error(CONFIG_GENERAL_ERROR, "Invalid vrrp_garp_lower_prio_repeat '%s'", FMT_STR_VSLOT(strvec, 1));
                return;
        }

	global_data->vrrp_garp_lower_prio_rep = garp_lower_prio_rep;
}
