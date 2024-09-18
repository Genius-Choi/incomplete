static struct sc_card_driver * sc_get_driver(void)
{
	if (iso_ops == NULL)
		iso_ops = sc_get_iso7816_driver()->ops;
	asepcos_ops = *iso_ops;
	asepcos_ops.match_card        = asepcos_match_card;
	asepcos_ops.init              = asepcos_init;
	asepcos_ops.select_file       = asepcos_select_file;
	asepcos_ops.set_security_env  = asepcos_set_security_env;
	asepcos_ops.decipher          = asepcos_decipher;
	asepcos_ops.compute_signature = asepcos_compute_signature;
	asepcos_ops.create_file       = asepcos_create_file;
	asepcos_ops.delete_file       = asepcos_delete_file;
	asepcos_ops.list_files        = asepcos_list_files;
	asepcos_ops.card_ctl          = asepcos_card_ctl;
	asepcos_ops.pin_cmd           = asepcos_pin_cmd;
	asepcos_ops.card_reader_lock_obtained = asepcos_card_reader_lock_obtained;

	return &asepcos_drv;
}
