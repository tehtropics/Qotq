#pragma once
//include standard libraries
#include <windows.h>
#include <SDKDDKVer.h>
#include <string.h>
#include <vadefs.h>
#include <stdio.h>
#include <xstring>
#include <Psapi.h>
#include <thread>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <vector>
#include <time.h>
#include <WinUser.h>
#include <random>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <set>
#include <map>
#include <unordered_map>
#include <memory>
#include <thread>
#include <array>
#include <assert.h>
#include <deque>
#include <intrin.h>
#include <atomic>
#include <mutex>
//some defines
#define INRANGE(x, a, b) (x >= a && x <= b) 
#define getBits(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xA): (INRANGE(x, '0', '9') ? x - '0': 0))
#define getByte(x) (getBits(x[0]) << 4 | getBits(x[1]))

//sdk includes
#include "Utils.h"
#include "VFunc.h"
#include "VMT.h"
//forward declaration
class C_BaseEntity;
//valve(interfaces/classes/rest shit)
#include "Enums.h"
#include "Recv.h"
#include "BaseHandle.h"
#include "ClientClass.h"
#include "Color.h"
#include "CUserCmd.h"
#include "CViewSetup.h"
#include "GlobalVars.h"
#include "IAppSystem.h"
#include "IHandleEntity.h"
#include "QAngle.h"
#include "Vector.h"
#include "Vector2D.h"
#include "Vector4D.h"
#include "VMatrix.h"
#include "INetChannelInfo.h"
#include "IConVar.h"
#include "CBaseEntity.h"
#include "GlowObjectManager.h"

#include "IPanel.h"
#include "IClientMode.h"
#include "IBaseClientDLL.h"
#include "ISurface.h"
#include "IVEngineClient.h"
#include "ICvar.h"

//hooks 
#include "Hooks.h"

//features includes
#include "Glow.h"





//some sdk things 
using namespace std;
//using namespace VT;