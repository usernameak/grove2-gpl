// GroveEngine 2
// Copyright (C) 2020-2025 usernameak
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License, version 3, as
// published by the Free Software Foundation.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "UndoStack.h"

ged::action::UndoStack::UndoStack()
    : m_currentActionIndex(0) {}

bool ged::action::UndoStack::canUndo() const {
    return m_currentActionIndex > 0;
}

bool ged::action::UndoStack::undo() {
    if (!canUndo()) return false;

    m_actionStack[m_currentActionIndex - 1]->undo();
    m_currentActionIndex--;

    return true;
}

bool ged::action::UndoStack::canRedo() const {
    return m_currentActionIndex < m_actionStack.size();
}

bool ged::action::UndoStack::redo() {
    if (!canRedo()) return false;

    m_actionStack[m_currentActionIndex]->execute();
    m_currentActionIndex++;

    return true;
}

void ged::action::UndoStack::addAction(gnaPointer<Action> action) {
    m_actionStack.erase(m_actionStack.begin() + m_currentActionIndex, m_actionStack.end());
    m_actionStack.push_back(action);
    m_currentActionIndex++;
}

void ged::action::UndoStack::addAndExecuteAction(gnaPointer<Action> action) {
    if (m_currentActionIndex > 0 && m_currentActionIndex == m_actionStack.size()) {
        gnaPointer<Action> oldAction = m_actionStack[m_currentActionIndex - 1];
        if (oldAction->canBeReplacedWith(action)) {
            // replace old action
            m_actionStack[m_currentActionIndex - 1] = action;
            action->executeReplacing(oldAction);

            return;
        }
    }
    addAction(action);
    action->execute();
}
