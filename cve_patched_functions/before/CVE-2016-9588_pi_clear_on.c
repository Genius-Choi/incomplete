static inline void pi_clear_on(struct pi_desc *pi_desc)
{
	clear_bit(POSTED_INTR_ON,
  		  (unsigned long *)&pi_desc->control);
}
