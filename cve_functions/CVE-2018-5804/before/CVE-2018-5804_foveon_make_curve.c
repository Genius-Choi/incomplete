short * CLASS foveon_make_curve (double max, double mul, double filt)
{
  short *curve;
  unsigned i, size;
  double x;

  if (!filt) filt = 0.8;
  size = 4*M_PI*max / filt;
  if (size == UINT_MAX) size--;
  curve = (short *) calloc (size+1, sizeof *curve);
  merror (curve, "foveon_make_curve()");
  curve[0] = size;
  for (i=0; i < size; i++) {
    x = i*filt/max/4;
    curve[i+1] = (cos(x)+1)/2 * tanh(i*filt/mul) * mul + 0.5;
  }
  return curve;
}
