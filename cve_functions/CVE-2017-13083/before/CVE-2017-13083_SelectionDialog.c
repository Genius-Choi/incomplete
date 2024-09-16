int SelectionDialog(char* title, char* message, char** choices, int size)
{
	int ret;

	dialog_showing++;
	szMessageTitle = title;
	szMessageText = message;
	szDialogItem = choices;
	nDialogItems = size;
	ret = (int)MyDialogBox(hMainInstance, IDD_SELECTION, hMainDialog, SelectionCallback);
	dialog_showing--;

	return ret;
}
