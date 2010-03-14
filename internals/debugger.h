#pragma once

#include <stdio.h>
#define DEBUG(args...) fprintf(stderr, args); fflush(stderr)
#define TEST(stage, assertion) if(!(assertion)) { DEBUG("%s falied.\n", stage); return 1; };
