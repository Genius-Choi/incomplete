local void new_opts(void)
{
    single_compress(1);
#ifndef NOTHREAD
    finish_jobs();
#endif
}
