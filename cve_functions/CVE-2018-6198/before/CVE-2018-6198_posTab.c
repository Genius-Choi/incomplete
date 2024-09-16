posTab(int x, int y)
{
    TabBuffer *tab;

    if (mouse_action.menu_str && x < mouse_action.menu_width && y == 0)
	return NO_TABBUFFER;
    if (y > LastTab->y)
	return NULL;
    for (tab = FirstTab; tab; tab = tab->nextTab) {
	if (tab->x1 <= x && x <= tab->x2 && tab->y == y)
	    return tab;
    }
    return NULL;
}
