#ifndef JB_WING32_H
#define JB_WING32_H

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

HDC WINAPI WinGCreateDC(void);
BOOL WINAPI WinGRecommendDIBFormat(BITMAPINFO *bmi);
HBITMAP WINAPI WinGCreateBitmap(HDC hdc, BITMAPINFO *bmi, void **bits);
void *WINAPI WinGGetDIBPointer(HBITMAP hbmp, BITMAPINFO *bmi);
UINT WINAPI WinGSetDIBColorTable(HDC hdc, UINT start, UINT end, RGBQUAD *colors);
UINT WINAPI WinGGetDIBColorTable(HDC hdc, UINT start, UINT end, RGBQUAD *colors);
HPALETTE WINAPI WinGCreateHalftonePalette(void);
HBRUSH WINAPI WinGCreateHalftoneBrush(HDC hdc, COLORREF color, INT type);
BOOL WINAPI WinGStretchBlt(HDC hdcDst, INT xDst, INT yDst, INT widthDst, INT heightDst, HDC hdcSrc, INT xSrc, INT ySrc,
    INT widthSrc, INT heightSrc);
BOOL WINAPI WinGBitBlt(HDC hdcDst, INT xDst, INT yDst, INT width, INT height, HDC hdcSrc, INT xSrc, INT ySrc);

#ifdef __cplusplus
}
#endif

#endif /* JB_WING32_H */
