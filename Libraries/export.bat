@echo off

C:\Repos\nuget pack MyLibraries.nuspec
xcopy *.nupkg C:\LocalNuGetFeed\.
pause
