/******************************************************************
   Copyright 2013, Jiang Xiao-tang

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
******************************************************************/
#ifndef GENETIC_PROGRGAM_DEBUG_H
#define GENETIC_PROGRGAM_DEBUG_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string>
#include <memory>



//#define DEBUG_ON
// if not define build_release ,it will print log


#ifdef GL_BUILD_FOR_ANDROID
#include <android/log.h>
#define GLPRINT(format, ...) __android_log_print(ANDROID_LOG_INFO, "MagicToon", format,##__VA_ARGS__)
#else
#define GLPRINT(format, ...) printf(format,##__VA_ARGS__)
#endif


#ifdef BUILD_RELEASE

#define FUNC_PRINT(x)
#define FUNC_PRINT_ALL(x, type)


#else
#define FUNC_PRINT(x) GLPRINT(#x"=%d in %s, %d \n",x,  __func__, __LINE__);
#define FUNC_PRINT_ALL(x, type) GLPRINT(#x"= %"#type" in %s, %d \n",x,  __func__, __LINE__);

#endif

#define CHECK_POINTER(x) {if(NULL==x){FUNC_PRINT_ALL(x,p);break;}}

#if !((defined GL_BUILD_FOR_ANDROID))
#define GLASSERT(x) assert(x)
#else
#define GLASSERT(x) \
    {bool __result = (x);\
        if (!(__result))\
FUNC_PRINT((__result));\
;}
#endif


#ifdef __cplusplus
extern "C"{
#endif
#ifndef NOT_LINUX
#include <execinfo.h>
void dump_stack();
#endif
#ifdef __cplusplus
}
#endif

#endif
