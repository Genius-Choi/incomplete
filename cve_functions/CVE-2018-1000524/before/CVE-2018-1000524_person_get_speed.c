person_get_speed(const person_t* person, double* out_x_speed, double* out_y_speed)
{
	if (out_x_speed) *out_x_speed = person->speed_x;
	if (out_y_speed) *out_y_speed = person->speed_y;
}
