authentic_card_ctl(struct sc_card *card, unsigned long cmd, void *ptr)
{
	struct sc_context *ctx = card->ctx;
	struct sc_authentic_sdo *sdo = (struct sc_authentic_sdo *) ptr;

	switch (cmd) {
	case SC_CARDCTL_GET_SERIALNR:
		return authentic_get_serialnr(card, (struct sc_serial_number *)ptr);
	case SC_CARDCTL_AUTHENTIC_SDO_CREATE:
		sc_log(ctx, "CARDCTL SDO_CREATE: sdo(mech:%X,id:%X)", sdo->docp.mech, sdo->docp.id);
		return authentic_manage_sdo(card, (struct sc_authentic_sdo *) ptr, cmd);
	case SC_CARDCTL_AUTHENTIC_SDO_DELETE:
		sc_log(ctx, "CARDCTL SDO_DELETE: sdo(mech:%X,id:%X)", sdo->docp.mech, sdo->docp.id);
		return authentic_manage_sdo(card, (struct sc_authentic_sdo *) ptr, cmd);
	case SC_CARDCTL_AUTHENTIC_SDO_STORE:
		sc_log(ctx, "CARDCTL SDO_STORE: sdo(mech:%X,id:%X)", sdo->docp.mech, sdo->docp.id);
		return authentic_manage_sdo(card, (struct sc_authentic_sdo *) ptr, cmd);
	case SC_CARDCTL_AUTHENTIC_SDO_GENERATE:
		sc_log(ctx, "CARDCTL SDO_GENERATE: sdo(mech:%X,id:%X)", sdo->docp.mech, sdo->docp.id);
		return authentic_manage_sdo_generate(card, (struct sc_authentic_sdo *) ptr);
	}
	return SC_ERROR_NOT_SUPPORTED;
}
