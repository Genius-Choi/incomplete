static void jsB_new_String(js_State *J)
{
	js_newstring(J, js_gettop(J) > 1 ? js_tostring(J, 1) : "");
}
