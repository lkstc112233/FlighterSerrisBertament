#include "stdafx.h"

#include "Brush.h"
#include "utility.h"

SolidColorBrush::~SolidColorBrush() { SafeRelease(&brush); }
