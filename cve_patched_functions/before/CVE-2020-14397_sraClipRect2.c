sraClipRect2(int *x, int *y, int *x2, int *y2,
	    int cx, int cy, int cx2, int cy2) {
  if (*x < cx)
    *x = cx;
  if (*y < cy)
    *y = cy;
  if (*x >= cx2)
    *x = cx2-1;
  if (*y >= cy2)
    *y = cy2-1;
  if (*x2 <= cx)
    *x2 = cx+1;
  if (*y2 <= cy)
    *y2 = cy+1;
  if (*x2 > cx2)
    *x2 = cx2;
  if (*y2 > cy2)
    *y2 = cy2;
  return (*x2>*x) && (*y2>*y);
}
