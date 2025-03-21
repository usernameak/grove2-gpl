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

#include "SceneEmpty.h"

GTL_RTTI_DEFINE(grScene::Empty, GTL_RTTI_INHERITS(grScene::SceneObject));

GTL_DEFINE_OBJECT_CLONE(grScene::Empty);
NXF_SERIALIZABLE_DEFINE(grScene::Empty, GR_SCENE_DLLIMPEXP);

void grScene::Empty::cloneMembers(gnaWeakPointer<gtlCloneable> dest, gtlCloneContext &cctx) const {
    grScene::SceneObject::cloneMembers(dest, cctx);
}
