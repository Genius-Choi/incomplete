void QuantizeMultiplier(double double_multiplier, int32_t* quantized_multiplier,
                        int* left_shift) {
  if (double_multiplier < 1.0) {
    QuantizeMultiplierSmallerThanOneExp(double_multiplier, quantized_multiplier,
                                        left_shift);
  } else {
    QuantizeMultiplierGreaterThanOne(double_multiplier, quantized_multiplier,
                                     left_shift);
  }
}
