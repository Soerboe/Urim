/*
 * Copyright (C) Dag Henning Liodden Sørbø <daghenning@lioddensorbo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COLORS
#define COLORS

#include "color.h"
#include <QObject>

class Colors : public QObject {
    Q_OBJECT

public:
    Color red() {      return Color(220, 0, 0,     tr("Red"));}
    Color green() {    return Color(0, 200, 0,     tr("Green"));}
    Color blue() {     return Color(0, 0, 255,     tr("Blue"));}
    Color yellow() {   return Color(255, 255, 0,   tr("Yellow"));}
    Color white() {    return Color(255, 255, 255, tr("White"));}
    Color black() {    return Color(0, 0, 0,       tr("Black"));}
    Color grey() {     return Color(128, 128, 128, tr("Grey"));}
    Color darkRed() {  return Color(110, 0, 0,     tr("Dark red"));}
    Color darkBlue() { return Color(0, 0, 90,      tr("Dark blue"));}
    Color darkGreen() {return Color(0, 80, 0,      tr("Dark green"));}
    Color pink() {     return Color(255, 62, 150,  tr("Pink"));}
    Color purple() {   return Color(155, 48, 255,  tr("Purple"));}
    Color orange() {   return Color(255, 97, 3,    tr("Orange"));}
    Color brown() {    return Color(138, 54, 15,   tr("Brown"));}
};

#endif // COLORS

