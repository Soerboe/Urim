#include "drawingsession.h"
#include "nomoreuniqueresultsexception.h"
#include "randomgenerator.h"

using namespace std;

DrawingSession::DrawingSession(bool uniqueResults)
    : _uniqueResults(uniqueResults)
{
}

Drawing DrawingSession::draw()
{
    return _uniqueResults ? drawUnique() : drawNonUnique();
}

void DrawingSession::addGenerator(shared_ptr<RandomGenerator> generator)
{
    _generators.append(generator);
}

Drawing DrawingSession::drawNonUnique()
{
    Drawing drawing = doDraw();
    _drawings.append(drawing);
    return drawing;
}

Drawing DrawingSession::drawUnique()
{
    Drawing drawing;

    if ((unsigned long) _drawings.size() >= numberOfUniqueResults()) {
        throw NoMoreUniqueResultsException();
    }

    do {
        drawing = doDraw();
    } while (_drawings.contains(drawing));

    _drawings.append(drawing);
    return drawing;
}

Drawing DrawingSession::doDraw()
{
    Drawing drawing;

    foreach (shared_ptr<RandomGenerator> generator, _generators) {
        drawing.addLot((*generator)());
    }

    return drawing;
}

unsigned long DrawingSession::numberOfUniqueResults()
{
    unsigned long count = 1;
    foreach (shared_ptr<RandomGenerator> generator, _generators) {
        count *= generator->numberOfUniqueResults();
    }

    return count;
}
