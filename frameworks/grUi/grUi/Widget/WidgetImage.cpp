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

#include "WidgetImage.h"

GTL_RTTI_DEFINE(grUiWidgetImage, GTL_RTTI_INHERITS(grUiWidget));

grDimension grUiWidgetImage::initialMeasure(int biasedSize) {
    grDimension imageDim;
    if (m_dpiScaleImage) {
        imageDim = grUiUnitDimension{
            (int)(m_image.dstWidth * m_imageScale),
            (int)(m_image.dstHeight * m_imageScale)
        }
                       .toPixels(get_metricContext());
    } else {
        imageDim = grDimension{
            (int)(m_image.dstWidth * m_imageScale),
            (int)(m_image.dstHeight * m_imageScale)
        };
    }
    return get_baseInsets().outsetDimension(imageDim);
}

void grUiWidgetImage::draw(grUiRenderer *render) {
    grUiWidget::draw(render);

    grRectangle rc = get_baseInsets().insetDimensionToRect(get_size());
    render->drawSprite(rc.x, rc.y, m_image.withDstSize(rc.width, rc.height));
}
