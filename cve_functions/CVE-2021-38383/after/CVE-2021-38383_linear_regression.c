linear_regression(double *m, double *b, double *r2, const double *x, const double *y, int n)
{
  double x_val;
  double sum_x  = 0;
  double sum_x2 = 0;
  double sum_y  = 0;
  double sum_y2 = 0;
  double sum_xy = 0;
  double denom;
  int i;

  for (i = 0; i < n; i++)
    {
      x_val   = x ? x[i] : (double)i;
      sum_x  += x_val;
      sum_x2 += x_val * x_val;
      sum_y  += y[i];
      sum_y2 += y[i] * y[i];
      sum_xy += x_val * y[i];
    }

  denom = (n * sum_x2 - sum_x * sum_x);
  if (denom == 0)
    return -1;

  *m = (n * sum_xy - sum_x * sum_y) / denom;
  *b = (sum_y * sum_x2 - sum_x * sum_xy) / denom;
  if (r2)
    *r2 = (sum_xy - (sum_x * sum_y)/n) * (sum_xy - (sum_x * sum_y)/n) / ((sum_x2 - (sum_x * sum_x)/n) * (sum_y2 - (sum_y * sum_y)/n));

  return 0;
}
