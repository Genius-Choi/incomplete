BOOL SetTaskbarProgressState(TASKBAR_PROGRESS_FLAGS tbpFlags)
{
	if (ptbl == NULL)
		return FALSE;
	return !FAILED(ptbl->lpVtbl->SetProgressState(ptbl, hMainDialog, tbpFlags));
}
