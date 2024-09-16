currentURL(void)
{
    if (Currentbuf->bufferprop & BP_INTERNAL)
	return Strnew_size(0);
    return parsedURL2Str(&Currentbuf->currentURL);
}
