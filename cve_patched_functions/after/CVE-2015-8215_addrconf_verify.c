static void addrconf_verify(void)
{
	mod_delayed_work(addrconf_wq, &addr_chk_work, 0);
}
