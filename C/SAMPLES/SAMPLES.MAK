all: hanoi template vmm eas sort hello graphic style \
     dialog clipbrd semaph image clock npipe dllapi \
     queues dragdrop animals tp ipf worms wpcar jigsaw print \
     palette

animals:
    cd animals
    nmake -f animals.mak
    cd ..

ipf:
    cd ipf
    nmake -f ipf.mak
    cd ..

worms:
    cd worms
    nmake -f worms.mak
    cd ..

dllapi:
    cd dllapi
    nmake -f dllapi.mak
    cd ..

npipe:
    cd npipe
    nmake -f npipe.mak
    cd ..

tp:
    cd tp
    nmake -f tp.mak
    cd ..

vmm:
    cd vmm
    nmake -f vmm.mak
    cd ..

queues:
    cd queues
    nmake -f queues.mak
    cd ..

dragdrop:
    cd dragdrop
    nmake -f dragdrop.mak
    cd ..

style:
    cd style
    nmake -f style.mak
    cd ..

clock:
    cd clock
    nmake -f tkclock.mak
    cd ..

template:
    cd template
    nmake -f template.mak
    cd ..

hanoi:
    cd hanoi
    nmake -f hanoi.mak
    cd ..

eas:
    cd eas
    nmake -f eas.mak
    cd ..

sort:
    cd sort
    nmake -f sort.mak
    cd ..

hello:
    cd hello
    nmake -f hello.mak
    cd ..

graphic:
    cd graphic
    nmake -f graphic.mak
    cd ..

dialog:
    cd dialog
    nmake -f dialog.mak
    cd ..

clipbrd:
    cd clipbrd
    nmake -f clipbrd.mak
    cd ..

semaph:
    cd semaph
    nmake -f semaph.mak
    cd ..

image:
    cd image
    nmake -f image32.mak
    cd ..


wpcar:
    cd wpcar
    nmake -f car.mak
    cd ..


jigsaw:
    cd jigsaw
    nmake -f jigsaw.mak
    cd ..


print:
     cd print
     nmake -f prtsamp.mak
     cd ..


palette:
     cd palette
     nmake -f palette.mak
     cd ..
