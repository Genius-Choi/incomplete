ntp_exit(int retval)
{
	msyslog(LOG_ERR, "EXITING with return code %d", retval);
	exit(retval);
}
