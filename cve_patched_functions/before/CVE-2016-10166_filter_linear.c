double filter_linear(const double x) {
	double ax = fabs(x);
	if (ax < 1.0f) {
		return (1.0f - ax);
	}
	return 0.0f;
}
