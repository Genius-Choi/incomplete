void ListDialog(char* title, char* message, char** items, int size)
{
	dialog_showing++;
	szMessageTitle = title;
	szMessageText = message;
	szDialogItem = items;
	nDialogItems = size;
	MyDialogBox(hMainInstance, IDD_LIST, hMainDialog, ListCallback);
	dialog_showing--;
}
