#include "MyProduct.h"
#include "../libSnail/Factory.h"

snail::CFactory<CMyProductA> theCreatorOfA("ProductA");
snail::CFactory<CMyProductB> theCreatorOfB("ProductB");