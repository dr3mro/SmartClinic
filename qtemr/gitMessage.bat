@echo off
 git log -1 --pretty=%%B | sed "s/\n\n//"