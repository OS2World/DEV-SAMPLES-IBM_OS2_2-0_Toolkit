all: callrexx devinfo pmrexx rexxutil rxmacdll

callrexx:
    cd callrexx
    nmake -f callrexx.mak
    cd..

devinfo:
    cd devinfo
    nmake -f devinfo.mak
    cd..

pmrexx:
    cd pmrexx
    nmake -f pmrexx.mak
    cd..

rexxutil:
    cd rexxutil
    nmake -f rexxutil.mak
    cd..

rxmacdll:
    cd rxmacdll
    nmake -f macro.mak
    nmake -f rxnlsinf.mak
    cd..
