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

#include "SceneGeom.h"

#include <nxfSerialization/NXFFileWriter.h>
#include <nxfSerialization/NXFFileReader.h>

NXF_SERIALIZABLE_DEFINE(grScene::Geometry, GR_SCENE_DLLIMPEXP);
GTL_DEFINE_OBJECT_CLONE(grScene::Geometry);
GTL_RTTI_DEFINE(grScene::Geometry, GTL_RTTI_INHERITS(grScene::SceneObject));

grScene::Geometry::Geometry() {
}

template <nxfSerialization::SerializationInterface TSerializationInterface>
gnaStatus grScene::Geometry::serializationImpl(TSerializationInterface &proxy) {
    GNA_CHECK_STATUS(grScene::SceneObject::serializationImpl(proxy));

    GNA_CHECK_STATUS(proxy.serialize("mesh", m_mesh));
    GNA_CHECK_STATUS(proxy.serialize("material", material));

    return GNA_E_OK;
}

bool grScene::Geometry::rayCast(const gtlMath2::Ray &ray, grScene::RayCastResult &result) {
    if (grScene::SceneObject::rayCast(ray, result))
        return true;

    if (m_mesh->m_primitiveType == grRenderCore::Mesh::TYPE_TRIANGLES) {
        bool indexed              = true;
        uint32_t totalVertexCount = m_mesh->m_indexCount;
        if (totalVertexCount == grRenderCore::Mesh::INVALID_INDEX_COUNT) {
            totalVertexCount = m_mesh->m_vertexCount;
            indexed          = false;
        }

        bool hit                      = false;
        float minIntersectionDistance = result.intersectionDistance;

        for (uint32_t i = 0; i < totalVertexCount; i += 3) {
            gtlMath2::Vector3f verts[3];
            for (uint32_t j = 0; j < 3; j++) {
                uint32_t idx = indexed ? m_mesh->m_indices[i + j] : i + j;

                verts[j] = m_mesh->getVertex(idx).position();
                verts[j] *= m_globalTransform.scale;
                verts[j] *= m_globalTransform.rotation;
                verts[j] += m_globalTransform.translation;
            }
            float intersectionDistance;
            if (ray.intersectTriangle(verts[0], verts[1], verts[2], intersectionDistance)) {
                if (intersectionDistance <= minIntersectionDistance) {
                    hit                     = true;
                    minIntersectionDistance = intersectionDistance;
                }
            }
        }
        if (hit) {
            result.object               = this;
            result.intersectionDistance = minIntersectionDistance;
            return true;
        }
    }

    return false;
}

void grScene::Geometry::updateGlobalBounds() {
    gtlMath2::Vector3f corners[] = {
        { m_mesh->m_bboxMin.x, m_mesh->m_bboxMin.y, m_mesh->m_bboxMin.z },
        { m_mesh->m_bboxMax.x, m_mesh->m_bboxMin.y, m_mesh->m_bboxMin.z },
        { m_mesh->m_bboxMin.x, m_mesh->m_bboxMax.y, m_mesh->m_bboxMin.z },
        { m_mesh->m_bboxMax.x, m_mesh->m_bboxMax.y, m_mesh->m_bboxMin.z },
        { m_mesh->m_bboxMin.x, m_mesh->m_bboxMin.y, m_mesh->m_bboxMax.z },
        { m_mesh->m_bboxMax.x, m_mesh->m_bboxMin.y, m_mesh->m_bboxMax.z },
        { m_mesh->m_bboxMin.x, m_mesh->m_bboxMax.y, m_mesh->m_bboxMax.z },
        { m_mesh->m_bboxMax.x, m_mesh->m_bboxMax.y, m_mesh->m_bboxMax.z },
    };
    auto matrix = m_globalTransform.toMatrix4x3();

    m_globalBounds = { INFINITY, -INFINITY }; // FIXME: this stuff will not work with -ffast-math
    for (const auto &corner : corners) {
        auto newCorner = matrix * corner;

        if (newCorner.x < m_globalBounds.min.x) m_globalBounds.min.x = newCorner.x;
        if (newCorner.y < m_globalBounds.min.y) m_globalBounds.min.y = newCorner.y;
        if (newCorner.z < m_globalBounds.min.z) m_globalBounds.min.z = newCorner.z;

        if (newCorner.x > m_globalBounds.max.x) m_globalBounds.max.x = newCorner.x;
        if (newCorner.y > m_globalBounds.max.y) m_globalBounds.max.y = newCorner.y;
        if (newCorner.z > m_globalBounds.max.z) m_globalBounds.max.z = newCorner.z;
    }
}

void grScene::Geometry::cloneMembers(gnaWeakPointer<gtlCloneable> dest, gtlCloneContext &cctx) const {
    grScene::SceneObject::cloneMembers(dest, cctx);

    gnaWeakPointer<grScene::Geometry> cDest = dest.cast<grScene::Geometry>();
    cDest->m_mesh                     = m_mesh; // no copy!
    cDest->material                   = material ? material->clone(cctx).cast<grScene::MaterialInstance>() : nullptr;
}

void grScene::Geometry::set_mesh(gnaPointer<grRenderCore::Mesh> mesh) {
    if (m_mesh == mesh) return;
    m_mesh = mesh;
    initializeMesh();
}
