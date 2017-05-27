#pragma once
#ifndef SNAIL_REGRESSION_EXPORTS
#define SNAIL_REGRESSION_DLL_EXPORT __declspec(dllimport)
#else
#define SNAIL_REGRESSION_DLL_EXPORT __declspec(dllexport)
#endif