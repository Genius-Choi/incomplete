vrrp_garp_lower_prio_delay_handler(vector_t *strvec)
{
        unsigned delay;

        if (!read_unsigned_strvec(strvec, 1, &delay, 0, UINT_MAX / TIMER_HZ, true)) {
                report_config_error(CONFIG_GENERAL_ERROR, "vrrp_garp_lower_prio_delay '%s' invalid - ignoring", FMT_STR_VSLOT(strvec, 1));
                return;
        }

	global_data->vrrp_garp_lower_prio_delay = delay * TIMER_HZ;
}
