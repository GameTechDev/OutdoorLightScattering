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


#define LOG_ERROR(ErrorMsg, ...)\
{                                       \
    TCHAR FormattedErrorMsg[256];       \
    _stprintf_s(FormattedErrorMsg, sizeof(FormattedErrorMsg)/sizeof(FormattedErrorMsg[0]), ErrorMsg, __VA_ARGS__ ); \
    TCHAR FullErrorMsg[1024];           \
    _stprintf_s(FullErrorMsg, sizeof(FullErrorMsg)/sizeof(FullErrorMsg[0]), _T("The following error occured in the %s function() (%s, line %d):\n%s"), _T(__FUNCTION__), _T(__FILE__), __LINE__, FormattedErrorMsg); \
    MessageBox(NULL, FullErrorMsg, _T("Error"), MB_ICONERROR|MB_OK ); \
}

#define CHECK_HR(Result, ErrorMsg, ...)\
    if( FAILED(Result) )                \
        LOG_ERROR(ErrorMsg, __VA_ARGS__);

#define CHECK_HR_RET(Result, ErrorMsg, ...)\
    if( FAILED(Result) )                    \
    {                                       \
        LOG_ERROR(ErrorMsg, __VA_ARGS__);   \
        return Result;                      \
    }
