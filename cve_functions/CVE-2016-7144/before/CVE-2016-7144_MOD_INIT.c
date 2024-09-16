MOD_INIT(m_sasl)
{
	ClientCapability cap;
	
	MARK_AS_OFFICIAL_MODULE(modinfo);

	CommandAdd(modinfo->handle, MSG_SASL, m_sasl, MAXPARA, M_USER|M_SERVER);
	CommandAdd(modinfo->handle, MSG_SVSLOGIN, m_svslogin, MAXPARA, M_USER|M_SERVER);
	CommandAdd(modinfo->handle, MSG_AUTHENTICATE, m_authenticate, MAXPARA, M_UNREGISTERED);

	HookAdd(modinfo->handle, HOOKTYPE_LOCAL_CONNECT, 0, sasl_connect);
	HookAdd(modinfo->handle, HOOKTYPE_LOCAL_QUIT, 0, sasl_quit);

	memset(&cap, 0, sizeof(cap));
	cap.name = "sasl";
	cap.cap = PROTO_SASL;
	cap.visible = sasl_capability_visible;
	ClientCapabilityAdd(modinfo->handle, &cap);

	return MOD_SUCCESS;
}
