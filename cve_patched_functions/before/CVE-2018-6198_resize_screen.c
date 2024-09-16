resize_screen(void)
{
    need_resize_screen = FALSE;
    setlinescols();
    setupscreen();
    if (CurrentTab)
	displayBuffer(Currentbuf, B_FORCE_REDRAW);
}
