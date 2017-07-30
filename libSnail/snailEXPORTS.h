#pragma once
#ifndef SNAIL_EXPORTS
#define SNAIL_API __declspec(dllimport)
#else
#define SNAIL_API __declspec(dllexport)
#endif