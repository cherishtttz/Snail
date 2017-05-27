#pragma once
#include "../libSnail/BaseProduct.h"
#include "../libSnail/snailMacro.h"

class IMyBaseProduct : public snail::CBaseProduct
{
public:
	virtual ~IMyBaseProduct() {}

	virtual void printV() const = 0;

protected:
	IMyBaseProduct() {}
};

class CMyProductA : public IMyBaseProduct
{
public:
	CMyProductA() {}
	~CMyProductA() {}

	virtual void printV() const override { _Log("Hi, I am product A."); }
};

class CMyProductB : public IMyBaseProduct
{
public:
	CMyProductB() {}
	~CMyProductB() {}

	virtual void printV() const override { _Log("Hi, I am product B."); }
};