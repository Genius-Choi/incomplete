int CLASS foveon_apply_curve (short *t_curve, int i)
{
  if (abs(i) >= t_curve[0]) return 0;
  return i < 0 ? -t_curve[1-i] : t_curve[1+i];
}
