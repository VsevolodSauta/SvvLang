#pragma once

#include "internals/basics.h"

Creator(Stack);
Action(Stack, Push, Object object);
Action(Stack, Pop);
Action(Stack, Peek);
Action(Stack, Clean);
Action(Stack, Clone);
Action(Stack, IsEmpty);
