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
#include "DynamicQuadTreeNode.h"

// Template class implementing hierarchy array, which is a quad tree indexed by 
// quad tree node location
template <class T>
class HierarchyArray
{
public:
	T& operator [] (const SQuadTreeNodeLocation &at)
	{
		return m_data[at.level][at.horzOrder + (at.vertOrder << at.level)];
	}
	const T& operator [] (const SQuadTreeNodeLocation &at) const
	{
		return m_data[at.level][at.horzOrder + (at.vertOrder << at.level)];
	}

	void Resize(size_t numLevelsInHierarchy)
	{
		m_data.resize(numLevelsInHierarchy);
		if( numLevelsInHierarchy )
		{
			for(size_t level = numLevelsInHierarchy; level--; )
			{
				size_t numElementsInLevel = 1 << level;
				m_data[level].resize(numElementsInLevel*numElementsInLevel);
			}
		}
	}

	bool Empty() const
	{
		return m_data.empty();
	}

private:
	std::vector<std::vector<T> > m_data;
};


// end of file
