static int do_i2c_nm(struct cmd_tbl *cmdtp, int flag, int argc,
		     char *const argv[])
{
	return mod_i2c_mem (cmdtp, 0, flag, argc, argv);
}
