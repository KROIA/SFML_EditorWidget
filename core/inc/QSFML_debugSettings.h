#pragma once

#ifdef _DEBUG
#define QSFML_PROFILE_CANVAS_ENABLE
#define QSFML_PROFILE_CANVASOBJECT_ENABLE
#endif


// Canvas is green
#ifdef QSFML_PROFILE_CANVAS_ENABLE
#define QSFML_PROFILE_CANVAS(x) x
#else
#define QSFML_PROFILE_CANVAS(x)
#endif

// CanvasObject is orange
#ifdef QSFML_PROFILE_CANVASOBJECT_ENABLE
#define QSFML_PROFILE_CANVASOBJECT(x) x
#else
#define QSFML_PROFILE_CANVASOBJECT(x)
#endif
