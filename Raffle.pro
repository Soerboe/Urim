TEMPLATE = subdirs

SUBDIRS += \
    RaffleGUI \
    RaffleTest \
    RaffleLib

RaffleGUI.depends = RaffleLib
RaffleTest.depends = RaffleLib
