#pragma once
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

//Windows
#include <Windows.h>
#include <windowsx.h>
#include <wrl.h>

//Windows Media Foundation
#include <mfmediaengine.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <mferror.h>

//C (CPP PORTED)
#include <cmath>
#include <ctime>
#include <cassert>

//CPP
#include <iostream>
#include <memory>
#include <fstream>

//CPP STL (DS)
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <map>

//CPP STL
#include <numeric>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <mutex>

//tinyXML2
#include "TinyXML2/Inc/tinyxml2.h"

//DirectX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>

//Input (UNUSED)
//#include "DXTK/Inc/Keyboard.h"
//#include "DXTK/Inc/Mouse.h"
//#include "DXTK/Inc/GamePad.h"

//Audio
#include "DXTK/Inc/Audio.h"

//Graphic
#include "DXTK/Inc/BufferHelpers.h"
#include "DXTK/Inc/CommonStates.h"
#include "DXTK/Inc/DirectXHelpers.h"
#include "DXTK/Inc/Effects.h"
#include "DXTK/Inc/GeometricPrimitive.h"
#include "DXTK/Inc/GraphicsMemory.h"
#include "DXTK/Inc/Model.h"
#include "DXTK/Inc/PostProcess.h"
#include "DXTK/Inc/VertexTypes.h"

//Graphic Utility
#include "DXTK/Inc/PrimitiveBatch.h"
#include "DXTK/Inc/SpriteBatch.h"
#include "DXTK/Inc/SpriteFont.h"

//Texture Loader
#include "DXTK/Inc/WICTextureLoader.h"
#include "DXTK/Inc/DDSTextureLoader.h"

//Misc Utility
#include "DXTK/Inc/ScreenGrab.h"
#include "DXTK/Inc/SimpleMath.h"

//DirectX libs
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")

//Windows Media Foundation libs
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "mfreadwrite.lib")

//This lib supports x64(AMD64) only and should be built with /MT or /MTd compiler options
#ifdef _DEBUG
    #pragma comment(lib, "DirectXTK_DBG.lib")
    #pragma comment(lib, "TinyXML2_DBG.lib")
#else
    #pragma comment(lib, "DirectXTK.lib")
    #pragma comment(lib, "TinyXML2.lib")
#endif

/*              Engine FrameWork              */
 
//Engine DataTypes
#include "Core/Manager/CE_RedefinedDatas.h"

//Engine Singleton Template
#include "Core/Manager/CE_Singleton.h"

//Engine Systems
#include "Core/System/CE_SystemObjects.h"

//Engine Managers
#include "Core/Manager/CE_Managers.h"