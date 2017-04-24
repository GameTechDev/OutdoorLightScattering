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

#include <set>
#include <vector>
#include <sstream>

class CD3DShaderMacroHelper
{
public:
    CD3DShaderMacroHelper() : m_bIsFinalized(false) {}

    template<typename DefintionType>
	void AddShaderMacro( LPCSTR Name, DefintionType Definition )
	{
        assert( !m_bIsFinalized );
		std::ostringstream ss;
		ss << Definition;
		AddShaderMacro<LPCSTR>( Name, ss.str().c_str() );
	}

	template<>
	void AddShaderMacro( LPCSTR Name, LPCSTR Definition )
	{
        assert( !m_bIsFinalized );
		D3D_SHADER_MACRO NewMacro = 
		{
			Name,
			m_DefinitionsPull.insert(Definition).first->c_str()
		};
		m_Macroes.push_back(NewMacro);
	}

	template<>
	void AddShaderMacro( LPCSTR Name, bool Definition )
	{
        assert( !m_bIsFinalized );
		AddShaderMacro( Name, Definition ? "1" : "0");
	}
	
    void Finalize()
	{
		D3D_SHADER_MACRO LastMacro = {NULL, NULL};
		m_Macroes.push_back(LastMacro);
        m_bIsFinalized = true;
	}

	operator const D3D_SHADER_MACRO* ()
	{
        assert( !m_Macroes.size() || m_bIsFinalized );
        if( m_Macroes.size() && !m_bIsFinalized )
            Finalize();
        return m_Macroes.size() ? &m_Macroes[0] : NULL;
	}
    
private:

	std::vector< D3D_SHADER_MACRO > m_Macroes;
	std::set< std::string > m_DefinitionsPull;
    bool m_bIsFinalized;
};
