deleteFiles()
{
    Buffer *buf;
    char *f;

    for (CurrentTab = FirstTab; CurrentTab; CurrentTab = CurrentTab->nextTab) {
	while (Firstbuf && Firstbuf != NO_BUFFER) {
	    buf = Firstbuf->nextBuffer;
	    discardBuffer(Firstbuf);
	    Firstbuf = buf;
	}
    }
    while ((f = popText(fileToDelete)) != NULL) {
	unlink(f);
	if (enable_inline_image == 2 && strcmp(f+strlen(f)-4, ".gif") == 0) {
	    Str firstframe = Strnew_charp(f);
	    Strcat_charp(firstframe, "-1");
	    unlink(firstframe->ptr);
        }
    }
}
