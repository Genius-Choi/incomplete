rdpRdp* rdp_new(freerdp* instance)
{
	rdpRdp* rdp;

	rdp = (rdpRdp*) malloc(sizeof(rdpRdp));

	if (rdp != NULL)
	{
		ZeroMemory(rdp, sizeof(rdpRdp));

		rdp->instance = instance;
		rdp->settings = freerdp_settings_new((void*) instance);

		if (instance != NULL)
			instance->settings = rdp->settings;

		rdp->extension = extension_new(instance);
		rdp->transport = transport_new(rdp->settings);
		rdp->license = license_new(rdp);
		rdp->input = input_new(rdp);
		rdp->update = update_new(rdp);
		rdp->fastpath = fastpath_new(rdp);
		rdp->nego = nego_new(rdp->transport);
		rdp->mcs = mcs_new(rdp->transport);
		rdp->redirection = redirection_new();
		rdp->mppc_dec = mppc_dec_new();
		rdp->mppc_enc = mppc_enc_new(PROTO_RDP_50);
	}

	return rdp;
}
