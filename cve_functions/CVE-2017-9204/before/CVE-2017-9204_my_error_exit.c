static void my_error_exit(j_common_ptr cinfo)
{
	struct my_error_mgr* myerr = (struct my_error_mgr*)cinfo->err;
	longjmp(myerr->setjmp_buffer, 1);
}
