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

#pragma once

#include <vector>
#include "HierarchyArray.h"
#include "DynamicQuadTreeNode.h"

// Class implementing elevation data source
class CElevationDataSource
{
public:
    // Creates data source from the specified raw data file
    CElevationDataSource(LPCTSTR strSrcDemFile);
    virtual ~CElevationDataSource(void);

	void GetDataPtr(const UINT16* &pDataPtr, size_t &Pitch);
    
    // Returns minimal height of the whole terrain
    UINT16 GetGlobalMinElevation()const;

    // Returns maximal height of the whole terrain
    UINT16 GetGlobalMaxElevation()const;

    void RecomputePatchMinMaxElevations(const SQuadTreeNodeLocation &pos);
    
    void SetOffsets(int iColOffset, int iRowOffset){m_iColOffset = iColOffset; m_iRowOffset = iRowOffset;}
    void GetOffsets(int &iColOffset, int &iRowOffset)const{iColOffset = m_iColOffset; iRowOffset = m_iRowOffset;}

    float GetInterpolatedHeight(float fCol, float fRow, int iStep = 1)const;
    
    D3DXVECTOR3 ComputeSurfaceNormal(float fCol, float fRow,
                                     float fSampleSpacing,
                                     float fHeightScale, 
                                     int iStep = 1)const;

    unsigned int GetNumCols()const{return m_iNumCols;}
    unsigned int GetNumRows()const{return m_iNumRows;}
private:
    CElevationDataSource();

    // Calculates min/max elevations for all patches in the tree
    void CalculateMinMaxElevations();
    
    // Hierarchy array storing minimal and maximal heights for quad tree nodes
    HierarchyArray< std::pair<UINT16, UINT16> > m_MinMaxElevation;
    
    int m_iNumLevels;
    int m_iPatchSize;
    int m_iColOffset, m_iRowOffset;
    
    // The whole terrain height map
    std::vector<UINT16> m_TheHeightMap;
    unsigned int m_iNumCols, m_iNumRows;
};
