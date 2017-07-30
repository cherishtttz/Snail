#pragma once
#ifndef MACHINE_LEARNING_EXPORTS
#define MACHINE_LEARNING_API __declspec(dllimport)
#else
#define MACHINE_LEARNING_API __declspec(dllexport)
#endif