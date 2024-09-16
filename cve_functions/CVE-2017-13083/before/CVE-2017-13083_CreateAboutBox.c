INT_PTR CreateAboutBox(void)
{
	INT_PTR r;
	dialog_showing++;
	r = MyDialogBox(hMainInstance, IDD_ABOUTBOX, hMainDialog, AboutCallback);
	dialog_showing--;
	return r;
}
