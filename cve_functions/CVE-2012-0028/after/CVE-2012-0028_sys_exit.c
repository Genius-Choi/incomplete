asmlinkage long sys_exit(int error_code)
{
	do_exit((error_code&0xff)<<8);
}
