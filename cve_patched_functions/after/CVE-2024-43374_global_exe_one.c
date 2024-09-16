global_exe_one(char_u *cmd, linenr_T lnum)
{
    curwin->w_cursor.lnum = lnum;
    curwin->w_cursor.col = 0;
    if (*cmd == NUL || *cmd == '\n')
	do_cmdline((char_u *)"p", NULL, NULL, DOCMD_NOWAIT);
    else
	do_cmdline(cmd, NULL, NULL, DOCMD_NOWAIT);
}
