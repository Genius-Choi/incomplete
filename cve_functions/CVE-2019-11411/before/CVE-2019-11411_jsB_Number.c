static void jsB_Number(js_State *J)
{
	js_pushnumber(J, js_gettop(J) > 1 ? js_tonumber(J, 1) : 0);
}
