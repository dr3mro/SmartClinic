// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef GLOBALVARIABLES
#define GLOBALVARIABLES

#define STR_IMPL_(x) #x      //stringify argument
#define STR(x) STR_IMPL_(x)  //indirection to expand argument macros


#define BUILDVER 35
#define MINORVER 8
#define MAJORVER 3

#define APPNAME "SMARTCLINIC"
#define APPVERSION STR(MAJORVER) "." STR(MINORVER) "." STR(BUILDVER)
#define APPNAMEVER APPNAME " " APPVERSION
#define singleInstance "COM.SMARTSOFT.SMARTCLINIC3"
#define DEVELOPER "AMR OSMAN"
#define APPYEAR STR(2022)
#define COMMENTS ""
#define EXENAME "smartClinic3.exe"
#define whiteListUrl "https://dl.dropboxusercontent.com/s/m3p1ldvusb1ug0y/validKeys?dl=0"

#define updatePackageDir "updatePKGs"

#ifdef __GNUC__
#define updateInfo "https://dl.dropboxusercontent.com/s/e3uv38igk8ahry2/updateInfo7?dl=0"
#define updatePacakgeFile "updatePKGs/sc7.pkg"
#define updateInfoFile "updateInfo7"
#define pkgUrl "https://dl.dropboxusercontent.com/s/5ryt5gg0e2cr2ac/sc7.pkg?dl=0"
#elif _MSC_VER
#define updateInfo "https://dl.dropboxusercontent.com/s/fy9ork77kzpfkr7/updateInfo?dl=0"
#define updatePacakgeFile "updatePKGs/sc.pkg"
#define updateInfoFile "updateInfo"
#define pkgUrl "https://dl.dropboxusercontent.com/s/kz0zb1ich48aolq/sc.pkg?dl=0"
#endif

#define updateInfo_ "http://127.0.0.1:8000/update/update"
#define blockRegKey "Default"
#define activateRegKey "Activated"
#define blockregPath "HKEY_CURRENT_USER\\Software\\cortex64"
//#define selfEmail "smartclinic22@gmail.com" my1stlov // unsecure mode on
#define selfEmail "smartclinic3x.app@gmail.com" // secure mode on with app pass on
#define selfPass "xgbavzirteiudizs"
#define devEmail "dr3mro@gmail.com"
#define exeBackUp "backup/~smartClinic3.exe"
#define dbVersion 2.88
#define minimumDatabaseVersion 2.80
#define conditionsVersion 1.0
#define drugsDatabaseVer 210129
#define PORTABILITYLOCK ".portable"
#define HEADERFILE "header.html"
#define FOOTERFILE "footer.html"
#define BANNERFILE "banner.html"
#define LOGOFILE "logo.jpg"

#endif // GLOBALVARIABLES
