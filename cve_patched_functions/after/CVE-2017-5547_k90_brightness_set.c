static void k90_brightness_set(struct led_classdev *led_cdev,
			       enum led_brightness brightness)
{
	struct k90_led *led = container_of(led_cdev, struct k90_led, cdev);

	led->brightness = brightness;
	schedule_work(&led->work);
}
