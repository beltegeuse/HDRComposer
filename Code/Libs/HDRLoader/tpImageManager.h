#pragma once

#include "tpImage.hpp"
#include "tpSingleton.h"

class TP_EXPORT tpImageManager : public tpSingleton<tpImageManager>
{
private:
	friend class tpSingleton<tpImageManager>;

	tpImageManager(void);
	~tpImageManager(void);
};
