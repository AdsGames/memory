@echo off
set /p MAGICKDIR="ImageMagick Directory (Default: C:\Program Files\ImageMagick-7.1.0-Q16-HDRI): " || set "MAGICKDIR=C:\Program Files\ImageMagick-7.1.0-Q16-HDRI"
@echo on

if not exist "./out" md "./out"

for %%a in (./*.png) do "%MAGICKDIR%\magick.exe" convert "%%~a" -transparent "rgb(255,0,255)" "./out/%%~nxa"

@echo "Done!"

pause