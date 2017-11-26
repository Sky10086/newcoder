#!/bin/bash
echo "del early cache"
rm -rf Cmake*
rm -r sky_newcoder*
rm -r Debug
rm -r Release
rm cmake*
echo "gen new project"
cmake .. -DDEBUG=true  -G Xcode
open ./sky_newcoder.xcodeproj
