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

#pragma once
#ifndef _AIMLib_ImageAnnotationStatement_Class_
#define _AIMLib_ImageAnnotationStatement_Class_

namespace aim_lib
{
	//typedef AnnotationStatement ImageAnnotationStatement;
	class AIMLIB_API ImageAnnotationStatement : public AnnotationStatement
	{
	public:
		virtual ~ImageAnnotationStatement(void){
		}
	protected:
		ImageAnnotationStatement(void){
		}

		ImageAnnotationStatement(const iso_21090::II& subjectUid, const iso_21090::II& objectUid) : AnnotationStatement(subjectUid, objectUid){
		}

		ImageAnnotationStatement(const ImageAnnotationStatement& statement) : AnnotationStatement(statement){
		}
	};

	typedef std::vector<AnnotationStatement*> ImageAnnotationStatementPtrVector;

	class ImageAnnotation;

	// Using macro
	AIM_STMT_DECL(DicomImageReferenceEntityHasCalculationEntityStatement, DicomImageReferenceEntity, CalculationEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(DicomImageReferenceEntityHasImagingObservationEntityStatement, DicomImageReferenceEntity, ImagingObservationEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(DicomImageReferenceEntityHasImagingPhysicalEntityStatement, DicomImageReferenceEntity, ImagingPhysicalEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(DicomSegmentationEntityHasImagingObservationEntityStatement, DicomSegmentationEntity, ImagingObservationEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(GeneralLesionObservationEntityHasImagingPhysicalEntityStatement, GeneralLesionObservationEntity, ImagingPhysicalEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(ImageAnnotationHasCalculationEntityStatement, ImageAnnotation, CalculationEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(ImageAnnotationHasChildImageAnnotationStatement, ImageAnnotation, ImageAnnotation, HasChildAnnotationStatementRelationship, ImageAnnotationStatement)
	
	AIM_STMT_DECL(ImageAnnotationHasDicomImageReferenceEntityStatement, ImageAnnotation, DicomImageReferenceEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(ImageAnnotationHasDicomSegmentationEntityStatement, ImageAnnotation, DicomSegmentationEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(ImageAnnotationHasGeneralLesionObservationEntityStatement, ImageAnnotation, GeneralLesionObservationEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(ImageAnnotationHasImagingObservationEntityStatement, ImageAnnotation, ImagingObservationEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(ImageAnnotationHasImagingPhysicalEntityStatement, ImageAnnotation, ImagingPhysicalEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(ImageAnnotationHasInferenceEntityStatement, ImageAnnotation, InferenceEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(ImageAnnotationHasTextAnnotationEntityStatement, ImageAnnotation, TextAnnotationEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(ImageAnnotationHasThreeDimensionGeometricShapeEntityStatement, ImageAnnotation, ThreeDimensionGeometricShapeEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(ImageAnnotationHasTwoDimensionGeometricShapeEntityStatement, ImageAnnotation, TwoDimensionGeometricShapeEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(ImageAnnotationHasTimePointLesionObservationEntityStatement, ImageAnnotation, TimePointLesionObservationEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(ImageAnnotationHasUriImageReferenceEntityStatement, ImageAnnotation, UriImageReferenceEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	
	AIM_STMT_DECL(ImagingObservationEntityIsIdentifiedByThreeDimensionGeometricShapeEntityStatement, ImagingObservationEntity, ThreeDimensionGeometricShapeEntity, IsIdentifiedByAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(ImagingObservationEntityIsIdentifiedByTwoDimensionGeometricShapeEntityStatement, ImagingObservationEntity, TwoDimensionGeometricShapeEntity, IsIdentifiedByAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(ImagingObservationEntityIsIdentifiedByTextAnnotationEntityStatement, ImagingObservationEntity, TextAnnotationEntity, IsIdentifiedByAnnotationStatementRelationship, ImageAnnotationStatement)
	
	AIM_STMT_DECL(ImagingPhysicalEntityHasThreeDimensionGeometricShapeEntityStatement, ImagingPhysicalEntity, ThreeDimensionGeometricShapeEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(ImagingPhysicalEntityHasTwoDimensionGeometricShapeEntityStatement, ImagingPhysicalEntity, TwoDimensionGeometricShapeEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(ImagingPhysicalEntityHasTextAnnotationEntityStatement, ImagingPhysicalEntity, TextAnnotationEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	
	AIM_STMT_DECL(ThreeDimensionGeometricShapeEntityIsComprisedOfThreeDimensionGeometricShapeEntityStatement, ThreeDimensionGeometricShapeEntity, ThreeDimensionGeometricShapeEntity, IsComprisedOfAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(ThreeDimensionGeometricShapeEntityExcludesThreeDimensionGeometricShapeEntityStatement, ThreeDimensionGeometricShapeEntity, ThreeDimensionGeometricShapeEntity, ExcludesAnnotationStatementRelationship, ImageAnnotationStatement)
	
	AIM_STMT_DECL(TimePointLesionObservationEntityHasImagingPhysicalEntityStatement, TimePointLesionObservationEntity, ImagingPhysicalEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)

	AIM_STMT_DECL(TwoDimensionGeometricShapeEntityIsComprisedOfTwoDimensionGeometricShapeEntityStatement, TwoDimensionGeometricShapeEntity, TwoDimensionGeometricShapeEntity, IsComprisedOfAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(TwoDimensionGeometricShapeEntityExcludesTwoDimensionGeometricShapeEntityStatement, TwoDimensionGeometricShapeEntity, TwoDimensionGeometricShapeEntity, ExcludesAnnotationStatementRelationship, ImageAnnotationStatement)
	
	AIM_STMT_DECL(UriImageReferenceEntityHasImagingObservationEntityStatement, UriImageReferenceEntity, ImagingObservationEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(UriImageReferenceEntityHasImagingPhysicalEntityStatement, UriImageReferenceEntity, ImagingPhysicalEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
	AIM_STMT_DECL(UriImageReferenceEntityHasCalculationEntityStatement, UriImageReferenceEntity, CalculationEntity, HasAnnotationStatementRelationship, ImageAnnotationStatement)
}
#endif // _AIMLib_ImageAnnotationStatement_Class_
