#pragma once

#define BITMASK_TO_RIGHT(bound) (~(-(1 << (bound))))
#define BITMASK_TO_LEFT(bound) (-(1 << (bound)))
#define BITMASK_LEFTMOST(quantity) BITMASK_TO_LEFT(8 - quantity)
#define BITMASK_RIGHTMOST(quantity) BITMASK_TO_RIGHT(quantity + 1)
#define BITMASK(left, right)  (BITMASK_TO_LEFT(to) & BITMASK_TO_RIGHT(from))