#include "drawingsession.h"

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
