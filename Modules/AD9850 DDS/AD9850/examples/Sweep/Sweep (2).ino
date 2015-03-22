#include <AD9850.h>

/* MAP DIGITAL IO */
const int CLK_Pin = 22;
const int FQ_Pin = 23;
const int DATA_Pin = 24;

/* CREATE AD9850 CLASS INSTANCE */
AD9850 ad(CLK_Pin, FQ_Pin, DATA_Pin); // w_clk, fq_ud, d7


void setup() {}

// sweep form 1MHz to 10MHz
void loop() {
  for (uint32_t i = 1e3; i < 4e3; i++) {
    ad.setfreq(i);
  }
}
