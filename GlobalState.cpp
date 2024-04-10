#include "GlobalState.h"
GlobalState& getGlobalState() {
	static GlobalState G;
	return G;
}