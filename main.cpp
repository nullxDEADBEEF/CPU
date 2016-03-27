#include "cpu.h"

int main() {
  printf("====================\n");
  printf("     Virtual CPU\n");
  printf("====================\n");

	printf("control_unit.accumilator before fetch and decoding: %d\n", control_unit.accumilator);

  // This is for testing
  for( int i = 0; i <= 2; i++ ) {
    decode_and_execute_test();
  }

	printf("control_unit.accumilator after fetch and decoding: %d\n", control_unit.accumilator);

  // this is just for the command line to not close instantly
  getchar();

  return 0;
}
