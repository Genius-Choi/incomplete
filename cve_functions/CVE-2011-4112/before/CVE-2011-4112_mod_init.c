static int __init mod_init(void)
{
	register_hdlc_protocol(&proto);
	return 0;
}
