/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "../stdafx.h"

#include "Entity.h"
#include "MarkupEntity.h"
#include "GeometricShapeEntity.h"
#include "TwoDimensionSpatialCoordinate.h"
#include "TwoDimensionGeometricShapeEntity.h"
#include "TwoDimensionCircle.h"

#include "../memdebug.h"

using namespace aim_lib;

TwoDimensionCircle::TwoDimensionCircle() : TwoDimensionGeometricShapeEntity(C_SHAPE_NAME_CIRCLE_2D, 2){
}

TwoDimensionCircle::TwoDimensionCircle(const TwoDimensionCircle& twoDimensionCircle) : TwoDimensionGeometricShapeEntity(twoDimensionCircle){
}

TwoDimensionCircle::~TwoDimensionCircle(){
}

TwoDimensionCircle* TwoDimensionCircle::Clone() const{
	return new TwoDimensionCircle(*this);
}

const TwoDimensionGeometricShapeEntity::TwoDimensionShapeType TwoDimensionCircle::GetShapeType() const{
	return Circle_2D;
}

const TwoDimensionSpatialCoordinate& TwoDimensionCircle::GetCenter() const{
	assert(_twoDimensionSpatialCoordinateCollection.size() > CenterPoint);
	return _twoDimensionSpatialCoordinateCollection[CenterPoint];
}

const TwoDimensionSpatialCoordinate& TwoDimensionCircle::GetRadiusPoint() const{
	assert(_twoDimensionSpatialCoordinateCollection.size() > CircumferencePoint);
	return _twoDimensionSpatialCoordinateCollection[CircumferencePoint];
}

void TwoDimensionCircle::SetCenter(const TwoDimensionSpatialCoordinate& center){
	assert(_twoDimensionSpatialCoordinateCollection.size() > CenterPoint);
	_twoDimensionSpatialCoordinateCollection[CenterPoint] = center;
}

void TwoDimensionCircle::SetRadiusPoint(const TwoDimensionSpatialCoordinate& radiusPoint){
	assert(_twoDimensionSpatialCoordinateCollection.size() > CircumferencePoint);
	_twoDimensionSpatialCoordinateCollection[CircumferencePoint] = radiusPoint;
}
