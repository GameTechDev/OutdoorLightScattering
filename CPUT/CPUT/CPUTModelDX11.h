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
#ifndef __CPUTMODELDX11_H__
#define __CPUTMODELDX11_H__

#include "CPUTModel.h"
#include "CPUT_DX11.h"

class CPUTMeshDX11;
class CPUTRenderParametersDX;
class CPUTMaterialDX11;

//--------------------------------------------------------------------------------------
struct CPUTModelConstantBuffer
{
    XMMATRIX  World;
	XMMATRIX  WorldViewProjection;
    XMMATRIX  InverseWorld;
    XMVECTOR  LightDirection;
    XMVECTOR  EyePosition;
    XMMATRIX  LightWorldViewProjection;
    XMMATRIX  ViewProjection;
    XMVECTOR  BoundingBoxCenterWorldSpace;
    XMVECTOR  BoundingBoxHalfWorldSpace;
    XMVECTOR  BoundingBoxCenterObjectSpace;
    XMVECTOR  BoundingBoxHalfObjectSpace;
};

//--------------------------------------------------------------------------------------
class CPUTModelDX11 : public CPUTModel
{
protected:
    ID3D11Buffer      *mpModelConstantBuffer;

    // Destructor is not public.  Must release instead of delete.
    ~CPUTModelDX11(){ SAFE_RELEASE(mpModelConstantBuffer); }

public:
    CPUTModelDX11() :
        mpModelConstantBuffer(NULL)
    {}

    CPUTMeshDX11 *GetMesh(const UINT index) const;
    CPUTResult    LoadModel(CPUTConfigBlock *pBlock, int *pParentID, CPUTModel *pMasterModel=NULL);
    void          SetRenderStates(CPUTRenderParameters &renderParams);
    void          Render(CPUTRenderParameters &renderParams);
    void          RenderShadow(CPUTRenderParameters &renderParams);
    void          SetMaterial(UINT ii, CPUTMaterial *pMaterial);
    void          DrawBoundingBox(CPUTRenderParameters &renderParams);
};


#endif // __CPUTMODELDX11_H__