#ifndef INCLUDE_ALL_H
#define INCLUDE_ALL_H

#include <sys/stat.h>
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#include "utils/saveSystem.h"
#include "loginScreen/loginScreen.h"
#include "games/pong.h"
#include "games/math.h"
#include "games/simonSays.h"
#include "games/wordGrid.h"
#include "audioCheck/audioCheckScreen.h"

#include "chatScreen/triggerWordContainer.h"
#include "chatScreen/lineContainer.h"
#include "chatScreen/ai.h"
#include "twoFaScreen/twoFaScreen.h"
#include "chatScreen/chatScreen.h"
#include "boomboxInterface/boomboxInterface.h"
#include "stageFour.h"
#include "stageFive.h"
#include "stageSix.h"
#include "stageSeven.h"
#include "stageEight.h"
#include "stageNine.h"
#include "stageTen.h"
#include "soundPlayer.h"
#include "utils/safeFunctions.h"
#include "usbChecker/usbChecker.h"

#endif // INCLUDE_ALL_H
