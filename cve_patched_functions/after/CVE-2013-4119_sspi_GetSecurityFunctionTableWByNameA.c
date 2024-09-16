SecurityFunctionTableW* sspi_GetSecurityFunctionTableWByNameA(const SEC_CHAR* Name)
{
	SEC_WCHAR* NameW = NULL;
	SecurityFunctionTableW* table;

	ConvertToUnicode(CP_UTF8, 0, Name, -1, &NameW, 0);

	table = sspi_GetSecurityFunctionTableWByNameW(NameW);
	free(NameW);

	return table;
}
