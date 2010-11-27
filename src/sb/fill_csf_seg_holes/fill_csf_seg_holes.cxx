/*=========================================================================
  
  Copyright 2002, 2006-2010, Dr. Sandra Black
  Linda C. Campbell Cognitive Neurology Unit
  Sunnybrook Health Sciences Center
  
  This file is part of the Sunnybrook Image Software Processing (SIPS) package

  SIPS is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

=========================================================================*/

#include <string>
#include <iostream>

#include "../Common/itk_imgio_util_templates.h"
#include "../Common/itk_imgmath_util_templates.h"

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageRegionIterator.h"

void Usage( char* argv[] )
{
	std::cout << "Usage:" << std::endl;
	std::cout << "  " << argv[0] << " imgSEG imgHfB csf_value imgOUT" << std::endl;
	std::cout << std::endl;
	std::cout << "Input:" << std::endl;
  std::cout << "  imgSEG:    segmentation image "  << std::endl;
  std::cout << "  imgHfB:    head-from-brain image"  << std::endl;
  std::cout << "  csf_value: value for csf on segmentation" << std::endl;
  std::cout << "  imgOUT:    output image" << std::endl;
	std::cout << std::endl;
	std::cout << "Notes:" << std::endl;
	std::cout << "  -file extension required (.img/.nii/.nii.gz)" << std::endl;
  std::cout << "  -HfB image must have zeros for background"  << std::endl;
	std::cout << std::endl;
	exit(1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[] )
{
	
  if ( argc < 5 )
    Usage( argv );

	const int Dim = 3;
	typedef double PixelType;
	typedef itk::Image< PixelType, Dim > ImageType;
	typedef itk::ImageFileReader< ImageType > ReaderType;

  ReaderType::Pointer seg = ReaderType::New();
  seg->SetFileName( argv[1] );

	ReaderType::Pointer hfb = ReaderType::New();
	hfb->SetFileName( argv[2] );

  if ( !egitk::ReadImage< PixelType, Dim >( seg ) || !egitk::ReadImage< PixelType, Dim >( hfb ) )
    exit(1);

  ImageType::SizeType hfbSize;
  hfbSize = hfb->GetOutput()->GetLargestPossibleRegion().GetSize();

  ImageType::SizeType segSize;
  segSize = seg->GetOutput()->GetLargestPossibleRegion().GetSize();

  for ( int i=0; i < Dim; ++ i )
  {
    if ( hfbSize[i] != segSize[i] )
    {
      std::cout << "Error: Unequal voxel sizes (Dimension " << i << ": " << hfbSize[i] <<" and " << segSize[i] << ")" << std::endl;
      exit(1);
    }
  }

  int csf_value = atoi( argv[3] );
  
  typedef itk::ImageRegionIterator< ImageType > ItType;

  ItType seg_it( seg->GetOutput(), seg->GetOutput()->GetLargestPossibleRegion() );
  ItType hfb_it( hfb->GetOutput(), hfb->GetOutput()->GetLargestPossibleRegion() );

  for ( seg_it.GoToBegin(), hfb_it.GoToBegin(); !seg_it.IsAtEnd(); ++seg_it, ++hfb_it )
  {
    if ( ( hfb_it.Get() == 8 || hfb_it.Get() == 1 ) && seg_it.Get() == 0 )
      seg_it.Set( csf_value );
  }

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  
  egitk::WriteImageSamePixelType< PixelType, Dim >( argv[4], seg, seg->GetOutput() );

	return 0;

}
