cd /d "D:\VS2019Code\TestSys\TestSys" &msbuild "TestSys.vcxproj" /t:sdvViewer /p:configuration="Release" /p:platform="x64" /p:SolutionDir="D:\VS2019Code\TestSys" 
exit %errorlevel% 