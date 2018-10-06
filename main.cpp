#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <algorithm>
#include "UP_API.h"

using namespace std;

int main(int argc, char *argv[]) {
	int res, opt;
	int monitorIndex = 0;
	UBYTE b8Val;

  int brightness = 0;

  // find monitor and connect
	res = GetAvailableMonitors(&b8Val);
	if (b8Val == 0 || res != MONITOR_SUCCESS) return 1;
	if ((monitorIndex + 1) > b8Val || monitorIndex < 0)	return 1;
	res = ConnectMonitor(monitorIndex);
	if (res != MONITOR_SUCCESS)	return 1;

  // read current brightness
  res = GetBrightness(&b8Val);
  if (res != MONITOR_SUCCESS) return 1;
  brightness = (int)b8Val;

  while ((opt = getopt(argc, argv, "s:u:d:")) != -1) {
    switch (opt) {
      case 's':
        brightness = max(0, min(100, atoi(optarg)));
        break;
      case 'u':
        brightness = max(0, min(100, (brightness + atoi(optarg))));
        break;
      case 'd':
        brightness = max(0, min(100, (brightness - atoi(optarg))));
        break;
      default:
        cerr << "Usage: dell-brightness [-s absolute_brightness]|[-u add_brighntess]|[-d subtract_brightness]\n";
        return 1;
    }
  }

  // set new brightness
	res = SetBrightness(brightness);
	return (res == MONITOR_SUCCESS);
}
