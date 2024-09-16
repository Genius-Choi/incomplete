exim_exit(int rc)
{
search_tidyup();
DEBUG(D_any)
  debug_printf(">>>>>>>>>>>>>>>> Exim pid=%d terminating with rc=%d "
    ">>>>>>>>>>>>>>>>\n", (int)getpid(), rc);
exit(rc);
}
