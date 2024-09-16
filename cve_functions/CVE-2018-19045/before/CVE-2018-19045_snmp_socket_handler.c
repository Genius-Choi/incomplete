snmp_socket_handler(vector_t *strvec)
{
	if (vector_size(strvec) > 2) {
		report_config_error(CONFIG_GENERAL_ERROR, "Too many parameters specified for snmp_socket - ignoring");
		return;
	}

	if (vector_size(strvec) < 2) {
		report_config_error(CONFIG_GENERAL_ERROR, "SNMP error : snmp socket name missing");
		return;
	}

	if (strlen(strvec_slot(strvec,1)) > PATH_MAX - 1) {
		report_config_error(CONFIG_GENERAL_ERROR, "SNMP error : snmp socket name too long - ignored");
		return;
	}

	if (global_data->snmp_socket) {
		report_config_error(CONFIG_GENERAL_ERROR, "SNMP socket already set to %s - ignoring", global_data->snmp_socket);
		return;
	}

	global_data->snmp_socket = MALLOC(strlen(strvec_slot(strvec, 1) + 1));
	strcpy(global_data->snmp_socket, strvec_slot(strvec,1));
}
