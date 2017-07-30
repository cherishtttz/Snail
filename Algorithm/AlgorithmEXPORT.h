#pragma once
#ifndef ALGORITHM_DLL_EXPORTS
#define ALGORITHM_API __declspec(dllimport)
#else
#define ALGORITHM_API __declspec(dllexport)
#endif