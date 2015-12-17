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

#ifndef DRAWINGVIEW_H
#define DRAWINGVIEW_H

#include <QMainWindow>
#include "drawingcontroller.h"
#include "drawingsetupdialog.h"
#include <QCloseEvent>

class ViewContainer;
class QLabel;
class QActionGroup;
class LoggerView;

namespace Ui {
class DrawingView;
}

class DrawingView : public QMainWindow
{
    Q_OBJECT

public:
    explicit DrawingView(DrawingController* controller, DrawingSetupDialog* setupDialog, QWidget* parent = 0);
    ~DrawingView();

    void setViewContainer(ViewContainer* viewContainer);
    ViewContainer* takeViewContainer();
    bool hasViewContainer();
    void enableDrawing(bool enabled);
    void setDrawingName(QString drawingName);

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::DrawingView *ui;
    DrawingController* _drawingController;
    DrawingSetupDialog* _setupDialog;
    ViewContainer* _viewContainer;
    QLabel* _sessionIdView;
    QActionGroup* _presentationViewActions;
    std::shared_ptr<LoggerView> _loggerView;

    void updateSessionIdView(const std::shared_ptr<DrawingSession> session);
    void setupLogger();
    void clear();

    void setupComponentVisibility(bool showViewContainerInWindow);

    void moveViewContainer(int screenIndex);

private slots:
    void setupPresentationViewMenu();
    void moveViewContainer(QAction*);
    void showDrawingSetup();
    void saveLogToFile();
    void drawClicked();
    void startNewDrawingSession(bool newDrawing = false);
    void showLogChecked(bool checked);
    void tooglePresentationView(bool checked);
    void createNewDrawingClicked();
    void showAbout();
    void showAboutQt();
    void screensChanged();
    void showLotsDrawnClicked(bool checked);
    void showSettingsDialog();
};

#endif // DRAWINGVIEW_H
