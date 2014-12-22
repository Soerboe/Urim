#include "drawingsession.h"

using namespace std;

DrawingSession::DrawingSession(bool uniqueResults)
    : _uniqueResults(uniqueResults)
{
}

Drawing DrawingSession::draw()
{
    Drawing drawing;
    foreach (shared_ptr<RandomGenerator> generator, _generators) {
        drawing.addLot((*generator)());
    }

    _drawings.append(drawing);
    return drawing;
}

void DrawingSession::addGenerator(shared_ptr<RandomGenerator> generator)
{
    _generators.append(generator);
}
