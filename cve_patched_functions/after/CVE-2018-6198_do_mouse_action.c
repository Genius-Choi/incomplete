do_mouse_action(int btn, int x, int y)
{
    MouseActionMap *map = NULL;
    int ny = -1;

    if (nTab > 1 || mouse_action.menu_str)
	ny = LastTab->y + 1;

    switch (btn) {
    case MOUSE_BTN1_DOWN:
	btn = 0;
	break;
    case MOUSE_BTN2_DOWN:
	btn = 1;
	break;
    case MOUSE_BTN3_DOWN:
	btn = 2;
	break;
    default:
	return;
    }
    if (y < ny) {
	if (mouse_action.menu_str && x >= 0 && x < mouse_action.menu_width) {
	    if (mouse_action.menu_map[btn])
		map = &mouse_action.menu_map[btn][x];
	}
	else
	    map = &mouse_action.tab_map[btn];
    }
    else if (y == LASTLINE) {
	if (mouse_action.lastline_str && x >= 0 &&
	    x < mouse_action.lastline_width) {
	    if (mouse_action.lastline_map[btn])
		map = &mouse_action.lastline_map[btn][x];
	}
    }
    else if (y > ny) {
	if (y == Currentbuf->cursorY + Currentbuf->rootY &&
	    (x == Currentbuf->cursorX + Currentbuf->rootX
#ifdef USE_M17N
	     || (WcOption.use_wide && Currentbuf->currentLine != NULL &&
		 (CharType(Currentbuf->currentLine->propBuf[Currentbuf->pos])
		  == PC_KANJI1)
		 && x == Currentbuf->cursorX + Currentbuf->rootX + 1)
#endif
	    )) {
	    if (retrieveCurrentAnchor(Currentbuf) ||
		retrieveCurrentForm(Currentbuf)) {
		map = &mouse_action.active_map[btn];
		if (!(map && map->func))
		    map = &mouse_action.anchor_map[btn];
	    }
	}
	else {
	    int cx = Currentbuf->cursorX, cy = Currentbuf->cursorY;
	    cursorXY(Currentbuf, x - Currentbuf->rootX, y - Currentbuf->rootY);
	    if (y == Currentbuf->cursorY + Currentbuf->rootY &&
		(x == Currentbuf->cursorX + Currentbuf->rootX
#ifdef USE_M17N
		 || (WcOption.use_wide && Currentbuf->currentLine != NULL &&
		     (CharType(Currentbuf->currentLine->
			       propBuf[Currentbuf->pos]) == PC_KANJI1)
		     && x == Currentbuf->cursorX + Currentbuf->rootX + 1)
#endif
		) &&
		(retrieveCurrentAnchor(Currentbuf) ||
		 retrieveCurrentForm(Currentbuf)))
		map = &mouse_action.anchor_map[btn];
	    cursorXY(Currentbuf, cx, cy);
	}
    }
    else {
	return;
    }
    if (!(map && map->func))
	map = &mouse_action.default_map[btn];
    if (map && map->func) {
	mouse_action.in_action = TRUE;
	mouse_action.cursorX = x;
	mouse_action.cursorY = y;
	CurrentKey = -1;
	CurrentKeyData = NULL;
	CurrentCmdData = map->data;
	(*map->func) ();
	CurrentCmdData = NULL;
    }
}
