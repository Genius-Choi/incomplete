snmp_rfc_handler(__attribute__((unused)) vector_t *strvec)
{
#ifdef _WITH_SNMP_RFCV2_
	global_data->enable_snmp_rfcv2 = true;
#endif
#ifdef _WITH_SNMP_RFCV3_
	global_data->enable_snmp_rfcv3 = true;
#endif
}
