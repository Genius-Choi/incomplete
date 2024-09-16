static int do_i2c_mm(struct cmd_tbl *cmdtp, int flag, int argc,
		     char *const argv[])
{
	return mod_i2c_mem (cmdtp, 1, flag, argc, argv);
}
