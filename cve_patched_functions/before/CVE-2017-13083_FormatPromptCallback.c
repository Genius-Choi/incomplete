static BOOL CALLBACK FormatPromptCallback(HWND hWnd, LPARAM lParam)
{
	char str[128];
	BOOL *found = (BOOL*)lParam;

	if (GetWindowTextU(hWnd, str, sizeof(str)) == 0)
		return TRUE;
	if (safe_strcmp(str, fp_button_str) == 0)
		*found = TRUE;
	return TRUE;
}
