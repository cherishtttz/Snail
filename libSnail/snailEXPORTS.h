#pragma once
#ifndef SNAIL_EXPORTS
#define SNAIL_DLL_EXPORT __declspec(dllimport)
#else
#define SNAIL_DLL_EXPORT __declspec(dllexport)
#endif