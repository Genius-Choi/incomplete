static void jsB_String(js_State *J)
{
	js_pushstring(J, js_gettop(J) > 1 ? js_tostring(J, 1) : "");
}
