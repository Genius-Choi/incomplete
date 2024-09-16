lldpd_hide_all(struct lldpd *cfg)
{
	struct lldpd_hardware *hardware;

	if (!cfg->g_config.c_smart)
		return;
	log_debug("smartfilter", "apply smart filter results on all ports");
	TAILQ_FOREACH(hardware, &cfg->g_hardware, h_entries) {
		if (cfg->g_config.c_smart & SMART_INCOMING_FILTER)
			lldpd_hide_ports(cfg, hardware, SMART_INCOMING);
		if (cfg->g_config.c_smart & SMART_OUTGOING_FILTER)
			lldpd_hide_ports(cfg, hardware, SMART_OUTGOING);
	}
}
