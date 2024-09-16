double CalculateDewPoint(double temp, int humidity)
{
	if (humidity==0)
		return temp;
	double dew_numer = 243.04*(log(double(humidity)/100.0)+((17.625*temp)/(temp+243.04)));
	double dew_denom = 17.625-log(double(humidity)/100.0)-((17.625*temp)/(temp+243.04));
	if (dew_numer==0)
		dew_numer=1;
	return dew_numer/dew_denom;
}
