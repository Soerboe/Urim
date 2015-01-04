TEMPLATE = subdirs

SUBDIRS += \
    gui \
    test \
    lib

gui.depends = lib
test.depends = lib
