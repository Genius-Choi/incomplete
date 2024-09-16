disp_srchresult(int result, char *prompt, char *str)
{
    if (str == NULL)
	str = "";
    if (result & SR_NOTFOUND)
	disp_message(Sprintf("Not found: %s", str)->ptr, TRUE);
    else if (result & SR_WRAPPED)
	disp_message(Sprintf("Search wrapped: %s", str)->ptr, TRUE);
    else if (show_srch_str)
	disp_message(Sprintf("%s%s", prompt, str)->ptr, TRUE);
}
