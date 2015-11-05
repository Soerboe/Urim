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

#ifndef GUIUTILS_H
#define GUIUTILS_H

#include <QFont>

#define MAX_FONT_SIZE 1000

static int calcMaxFontSize(const QFont& originalFont, const QString& text, const QRect& boundingBox)
{
    QFontMetrics originalMetrics(originalFont);
    bool fontTooLarge = originalMetrics.width(text) >= boundingBox.width() || originalMetrics.height() >= boundingBox.height();

    int inc = 2;
    int size = originalFont.pointSize();
    QFont f = originalFont;

    if (!fontTooLarge) {
        // try to increase font size
        for (int i = 1; i <= MAX_FONT_SIZE; i += inc) {
            f.setPointSize(size + i);
            QFontMetrics fm(f);
            if (fm.width(text) >= boundingBox.width() || fm.height() >= boundingBox.height()) {
                return size + i - inc;
            }
        }
    }

    if (fontTooLarge) {
        for (int i = 1; i <= MAX_FONT_SIZE && size - i > 1; i += inc) {
            // try to decrease font size
            f.setPointSize(size - i);
            QFontMetrics fm(f);
            if (fm.width(text) < boundingBox.width() && fm.height() < boundingBox.height()) {
                return size - i;
            }
        }
    }

    return size; // should never get this far
}

#endif // GUIUTILS_H

