#include "dice.h"

	int sides;

	dice::dice(int s) {
		sides = s;
	}

	dice::dice() {}
	int dice::getS() {
		return sides;
	}
