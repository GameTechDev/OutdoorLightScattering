/////////////////////////////////////////////////////////////////////////////////////////////
// Copyright 2017 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
/////////////////////////////////////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN

#pragma warning (disable: 4100 4127) // warning C4100:  unreferenced formal parameter;  warning C4127:  conditional expression is constant

#pragma warning (push)
#pragma warning (disable: 4201) // nonstandard extension used : nameless struct/union

//
// windows headers
//
#include <sdkddkver.h>
#include <Windows.h>
#include <tchar.h>
#include <atlcomcli.h> // for CComPtr support

//
// C++ headers
//

#include <cassert>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <ctime>

//
// DirectX headers
//
#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10math.h>
#include <xnamath.h>

#pragma warning (pop)

#include "Errors.h"

#include "CPUT.h"

#if defined(DEBUG) || defined(_DEBUG)
#ifndef V
#define V(x)           { hr = (x); assert(SUCCEEDED(hr)); }
#endif
#ifndef V_RETURN
#define V_RETURN(x)    { hr = (x); assert(SUCCEEDED(hr)); if( FAILED(hr) ) { return hr; } }
#endif
#else
#ifndef V
#define V(x)           { hr = (x); }
#endif
#ifndef V_RETURN
#define V_RETURN(x)    { hr = (x); if( FAILED(hr) ) { return hr; } }
#endif
#endif

//#define assert(x) if(!(x)) _CrtDbgBreak(); else {}

inline void UnbindPSResources(ID3D11DeviceContext *pCtx)
{
	ID3D11ShaderResourceView *pSRVs[20] = {NULL};
	pCtx->PSSetShaderResources(0, _countof(pSRVs), pSRVs);
}

inline void UnbindVSResources(ID3D11DeviceContext *pCtx)
{
	ID3D11ShaderResourceView *pSRVs[8] = {NULL};
	pCtx->VSSetShaderResources(0, _countof(pSRVs), pSRVs);
}

inline void UpdateConstantBuffer(ID3D11DeviceContext *pDeviceCtx, ID3D11Buffer *pCB, const void *pData, size_t DataSize)
{
    D3D11_MAPPED_SUBRESOURCE MappedData;
    pDeviceCtx->Map(pCB, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedData);
    memcpy(MappedData.pData, pData, DataSize);
    pDeviceCtx->Unmap(pCB, 0);
}

// end of file
