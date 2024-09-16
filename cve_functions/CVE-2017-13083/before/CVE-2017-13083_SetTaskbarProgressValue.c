BOOL SetTaskbarProgressValue(ULONGLONG ullCompleted, ULONGLONG ullTotal)
{
	if (ptbl == NULL)
		return FALSE;
	return !FAILED(ptbl->lpVtbl->SetProgressValue(ptbl, hMainDialog, ullCompleted, ullTotal));
}
