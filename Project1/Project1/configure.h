#pragma once

//通过预编译方式去掉unicode字符集
#ifdef UNICODE
#undef UNICODE
#endif 

#include <easyx.h>
#include <string>