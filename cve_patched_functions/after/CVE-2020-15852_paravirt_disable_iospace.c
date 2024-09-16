int paravirt_disable_iospace(void)
{
	return request_resource(&ioport_resource, &reserve_ioports);
}
